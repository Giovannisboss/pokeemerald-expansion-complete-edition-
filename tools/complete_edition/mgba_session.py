"""Persistent ordinary-input mGBA SDL QA runner. Basic runtime delivery observed.

Run with -u inside a persistent exec TTY. Supply JSON objects, one per line:
 {"action":"press","button":"A","hold":0.08}
 {"action":"hold","buttons":["B","UP"],"seconds":0.5}
 {"action":"pulse","button":"A","count":3,"hold":0.08,"gap":0.12}
 {"action":"wait","seconds":1}
 {"action":"shot"}   {"action":"status"}   {"action":"quit"}

Only normal input; no memory access, save-state loading, recopying saves, cheats,
rewind, focus changes, or caller-supplied Windows messages. Existing session
battery saves are preserved. Key posting is not proof of gameplay progress.
"""

import argparse
import ctypes
from ctypes import wintypes
import hashlib
import json
import math
import os
from pathlib import Path
import re
import subprocess
import sys
import time

from mgba_buttons import BUTTONS, EXPECTED_IMAGE, Win32, journal


ROM_SHA256 = "ab7793e8a2f73e56863c88daaf3d726b6ae515a78b8f67aed1f902651f14b040"
PLAYTEST_ROOT = Path(__file__).resolve().parents[2] / "work" / "playtest"
ORDINARY = frozenset(BUTTONS) - {"SCREENSHOT"}
SETTLE = 0.35


def within(path, root):
    resolved = path.resolve()
    if not resolved.is_relative_to(root.resolve()):
        raise ValueError("Path must stay inside the allowed session directory")
    return resolved


def bounded(value, lower, upper, name):
    if isinstance(value, bool) or not isinstance(value, (int, float)):
        raise ValueError(name + " must be numeric")
    value = float(value)
    if not math.isfinite(value) or not lower <= value <= upper:
        raise ValueError(f"{name} must be between {lower} and {upper}")
    return value


def button(value):
    if not isinstance(value, str) or value not in ORDINARY:
        raise ValueError("Require an ordinary GBA button: " + ", ".join(sorted(ORDINARY)))
    return value


def validate_command(raw):
    if not isinstance(raw, dict):
        raise ValueError("Each command must be a JSON object")
    action = raw.get("action")
    allowed = {
        "press": {"action", "button", "hold"},
        "hold": {"action", "buttons", "seconds"},
        "pulse": {"action", "button", "count", "hold", "gap"},
        "wait": {"action", "seconds"},
        "shot": {"action"}, "status": {"action"}, "quit": {"action"},
    }
    if not isinstance(action, str) or action not in allowed:
        raise ValueError("Unknown action")
    if set(raw) - allowed[action]:
        raise ValueError("Unexpected command fields")
    result = {"action": action}
    if action in {"press", "pulse"}:
        result["button"] = button(raw.get("button"))
        result["hold"] = bounded(raw.get("hold", 0.08), 0.02, 2.0, "hold")
    if action == "hold":
        keys = raw.get("buttons")
        if not isinstance(keys, list) or not 2 <= len(keys) <= 3:
            raise ValueError("hold requires two or three buttons")
        keys = [button(key) for key in keys]
        if len(set(keys)) != len(keys):
            raise ValueError("Simultaneous buttons must be distinct")
        result.update(buttons=keys, seconds=bounded(raw.get("seconds"), 0.02, 2, "seconds"))
    if action == "pulse":
        count = raw.get("count")
        if isinstance(count, bool) or not isinstance(count, int) or not 1 <= count <= 20:
            raise ValueError("count must be an integer from 1 through 20")
        gap = bounded(raw.get("gap", 0.12), 0.02, 2, "gap")
        if count * result["hold"] + (count - 1) * gap + SETTLE > 10:
            raise ValueError("Total pulse duration including settle must not exceed 10 seconds")
        result.update(count=count, gap=gap)
    if action == "wait":
        result["seconds"] = bounded(raw.get("seconds"), 0, 5, "seconds")
    return result


def newest_png(directory, stem):
    newest = None
    with os.scandir(directory) as entries:
        for entry in entries:
            if entry.name.startswith(stem + "-") and entry.name.lower().endswith(".png") and entry.is_file(follow_symlinks=False):
                stamp = (entry.stat(follow_symlinks=False).st_mtime_ns, entry.name)
                if newest is None or stamp > newest[0]:
                    newest = (stamp, Path(entry.path))
    return newest


class Session:
    def __init__(self, directory, rom):
        self.directory = directory
        self.rom = rom
        self.proc = None
        self.handle = None
        self.hwnd = None
        self.command_id = 0
        self.api = Win32()
        self.screenshots = within(directory / "screenshots", directory)
        self.logpath = within(directory / "emulator-output.log", directory)
        self.api.user.ShowWindow.argtypes = [wintypes.HWND, ctypes.c_int]
        self.api.user.ShowWindow.restype = wintypes.BOOL

    def record(self, event, **fields):
        journal({"runner": "mgba_session", "session": str(self.directory),
                 "pid": self.proc.pid if self.proc else None,
                 "command_id": self.command_id, "event": event, **fields})

    def start(self):
        self.screenshots.mkdir(exist_ok=True)
        startup = subprocess.STARTUPINFO()
        startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
        startup.wShowWindow = 0  # Hidden; never activate or focus the SDL window.
        argv = [EXPECTED_IMAGE, "-l", "7", "-C", "rewindEnable=0", "-C", "mute=1",
                "-C", "savegamePath=" + self.directory.as_posix(),
                "-C", "screenshotPath=" + self.screenshots.as_posix(), self.rom.name]
        self.record("launch_attempt", rom=self.rom.name, rom_sha256=ROM_SHA256)
        with self.logpath.open("ab", buffering=0) as log:
            self.proc = subprocess.Popen(argv, cwd=self.directory, stdin=subprocess.DEVNULL,
                                         stdout=log, stderr=subprocess.STDOUT,
                                         startupinfo=startup, creationflags=subprocess.CREATE_NO_WINDOW)
        # Creation can precede availability of limited process information.
        # Retry only this owned child's unchanged PID; image mismatches fail at once.
        process_deadline = time.monotonic() + 3
        while self.handle is None:
            if self.proc.poll() is not None:
                raise RuntimeError("Owned emulator exited during startup")
            try:
                self.handle = self.api.open_verified(self.proc.pid)
            except OSError as exc:
                if time.monotonic() >= process_deadline:
                    raise RuntimeError("Could not verify owned emulator within three seconds") from exc
                time.sleep(0.05)
        # SDL may replace its initial window while selecting a renderer.
        # Observe startup for at least two seconds, then require a stable HWND.
        startup_started = time.monotonic()
        deadline = startup_started + 5
        candidate = None
        candidate_since = None
        while time.monotonic() < deadline:
            self.api.ensure_running(self.handle)
            windows = [w for w in self.api.windows(self.proc.pid) if w["class"].startswith("SDL")]
            if len(windows) == 1:
                current = int(windows[0]["hwnd"], 0)
                try:
                    self.api.ensure_window(self.proc.pid, current)
                except RuntimeError:
                    candidate = None
                    candidate_since = None
                    time.sleep(0.05)
                    continue
                self.api.user.ShowWindow(current, 0)
                if current != candidate:
                    candidate = current
                    candidate_since = time.monotonic()
                if time.monotonic() - startup_started >= 2 and time.monotonic() - candidate_since >= 0.25:
                    self.hwnd = current
                    self.record("launched", hwnd=hex(self.hwnd))
                    return
            else:
                candidate = None
                candidate_since = None
            time.sleep(0.05)
        raise RuntimeError("No unique owned SDL window appeared within five seconds")

    def refresh_window(self):
        # Re-enumerate only the verified child. Never follow a global foreground HWND.
        deadline = time.monotonic() + 1
        while time.monotonic() < deadline:
            self.api.ensure_running(self.handle)
            windows = [w for w in self.api.windows(self.proc.pid) if w["class"].startswith("SDL")]
            if len(windows) == 1:
                current = int(windows[0]["hwnd"], 0)
                try:
                    self.api.ensure_window(self.proc.pid, current)
                except RuntimeError:
                    time.sleep(0.05)
                    continue
                if current != self.hwnd:
                    previous = self.hwnd
                    self.hwnd = current
                    self.api.user.ShowWindow(current, 0)
                    self.record("window_reacquired", previous_hwnd=hex(previous) if previous else None,
                                hwnd=hex(current))
                return current
            time.sleep(0.05)
        raise RuntimeError("No unique current SDL window for the verified owned child")

    def check(self):
        if not self.proc or self.proc.poll() is not None:
            raise RuntimeError("Owned emulator process is not running")
        self.api.ensure_running(self.handle)
        try:
            self.api.ensure_window(self.proc.pid, self.hwnd)
        except RuntimeError:
            self.refresh_window()

    def key_event(self, key, release):
        self.check()
        self.record("key_event_attempt", button=key, release=release)
        self.api.post_button(self.hwnd, *BUTTONS[key], release=release)
        self.record("key_event_posted", button=key, release=release)

    def held(self, keys, duration):
        attempted = []
        original_error = None
        try:
            for key in keys:
                attempted.append(key)
                self.key_event(key, False)
            time.sleep(duration)
        except BaseException as exc:
            original_error = exc
        finally:
            # Attempt every release even if another release/journal operation fails.
            for key in reversed(attempted):
                try:
                    self.check()
                    self.api.post_button(self.hwnd, *BUTTONS[key], release=True)
                    self.record("key_event_posted", button=key, release=True)
                except BaseException as exc:
                    if original_error is None:
                        original_error = exc
            if original_error is not None:
                raise original_error

    def shot(self):
        before = newest_png(self.screenshots, self.rom.stem)
        self.held(["SCREENSHOT"], 0.05)
        deadline = time.monotonic() + 3
        while time.monotonic() < deadline:
            newest = newest_png(self.screenshots, self.rom.stem)
            if newest and (before is None or newest[0] != before[0]) and newest[1].stat().st_size >= 24:
                return str(newest[1])
            self.check()
            time.sleep(0.05)
        raise RuntimeError("Native F12 did not create a new PNG within three seconds")

    def close(self):
        if self.proc and self.proc.poll() is None:
            # Only graceful WM_CLOSE, scoped to the verified owned SDL window.
            if self.handle is None:
                self.handle = self.api.open_verified(self.proc.pid)
            self.refresh_window()
            if self.hwnd is not None:
                self.api.ensure_window(self.proc.pid, self.hwnd)
                self.record("close_attempt", hwnd=hex(self.hwnd))
                if not self.api.user.PostMessageW(self.hwnd, 0x0010, 0, 0):
                    raise ctypes.WinError(ctypes.get_last_error())
                try:
                    self.proc.wait(timeout=5)
                except subprocess.TimeoutExpired:
                    raise RuntimeError("Graceful close timed out; emulator was not force-terminated")
            else:
                raise RuntimeError("Cannot gracefully close: no unique owned SDL window")
        if self.handle:
            self.api.kernel.CloseHandle(self.handle)
            self.handle = None
        return self.proc.returncode if self.proc else None

    def execute(self, command):
        action = command["action"]
        if action == "status":
            if self.proc.poll() is None:
                self.check()
            return {"pid": self.proc.pid, "running": self.proc.poll() is None,
                    "hwnd": hex(self.hwnd), "session": str(self.directory),
                    "input_runtime": "BASIC_OBSERVED; VERIFY_EACH_RESULT"}
        self.check()
        if action == "press":
            self.held([command["button"]], command["hold"])
            time.sleep(SETTLE)
        elif action == "hold":
            self.held(command["buttons"], command["seconds"])
            time.sleep(SETTLE)
        elif action == "pulse":
            for index in range(command["count"]):
                self.held([command["button"]], command["hold"])
                if index + 1 < command["count"]:
                    time.sleep(command["gap"])
            time.sleep(SETTLE)
        elif action == "wait":
            time.sleep(command["seconds"])
        elif action == "shot":
            return {"shot": self.shot()}
        elif action == "quit":
            return {"quit": True, "exit_code": self.close()}
        return {"posted": True, "gameplay_result": "REQUIRES_SCREENSHOT_OBSERVATION"}


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--session", required=True, type=Path, help="Existing directory within this task's work/playtest")
    parser.add_argument("--rom", default="CE_20261016_Verified.gba", help="ROM basename only; verified ab779 SHA required")
    args = parser.parse_args()
    directory = within(args.session, PLAYTEST_ROOT)
    if not directory.is_dir():
        parser.error("Session directory must already exist")
    if not re.fullmatch(r"[A-Za-z0-9_.-]+\.gba", args.rom, flags=re.I):
        parser.error("ROM must be a plain .gba basename")
    rom = within(directory / args.rom, directory)
    save = within((directory / args.rom).with_suffix(".sav"), directory)
    if not rom.is_file() or not save.is_file():
        parser.error("Verified ROM and existing matching .sav are required; runner never copies saves")
    if hashlib.sha256(rom.read_bytes()).hexdigest() != ROM_SHA256:
        parser.error("ROM SHA-256 does not match the verified build")
    if os.name != "nt":
        parser.error("Windows is required")
    session = Session(directory, rom)
    try:
        session.start()
        print(json.dumps({"ready": True, "pid": session.proc.pid, "session": str(directory),
                          "input_runtime": "BASIC_OBSERVED; VERIFY_EACH_RESULT"}), flush=True)
        for line in sys.stdin:
            session.command_id += 1
            command = None
            try:
                command = validate_command(json.loads(line))
                session.record("command", command=command)
                result = session.execute(command)
                session.record("command_result", action=command["action"], result=result)
                print(json.dumps(result), flush=True)
                if command["action"] == "quit":
                    break
            except (OSError, RuntimeError, ValueError, TypeError) as exc:
                session.record("command_error", command=command, error=str(exc))
                print(json.dumps({"error": str(exc)}), flush=True)
        return 0
    finally:
        session.close()


if __name__ == "__main__":
    try:
        sys.exit(main())
    except (OSError, RuntimeError, ValueError) as exc:
        print(json.dumps({"error": str(exc)}), flush=True)
        sys.exit(1)
