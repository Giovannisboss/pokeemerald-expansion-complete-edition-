"""Restricted ordinary-button helper for Windows mGBA SDL.

Win32 API delivery is observed through the owned-child session runner.
Standalone cross-process CLI delivery remains unverified.

No process-memory access, focus changes, savestates, or arbitrary key/messages.
`list` is read-only. `press` journals its attempt and outcome in this workspace.
"""

import argparse
import ctypes
from ctypes import wintypes
from datetime import datetime, timezone
import json
import os
from pathlib import Path
import sys
import time


EXPECTED_IMAGE = r"C:\Program Files\mGBA\mgba-sdl.exe"
JOURNAL = Path(__file__).resolve().parents[2] / "work" / "playtest" / "mgba_button_journal.jsonl"
# name -> Windows virtual key, hardware scan code, extended-key flag
BUTTONS = {
    "A": (0x58, 0x2D, False),       # X
    "B": (0x5A, 0x2C, False),       # Z
    "L": (0x41, 0x1E, False),       # A
    "R": (0x53, 0x1F, False),       # S
    "START": (0x0D, 0x1C, False),
    "SELECT": (0x08, 0x0E, False),
    "UP": (0x26, 0x48, True),
    "DOWN": (0x28, 0x50, True),
    "LEFT": (0x25, 0x4B, True),
    "RIGHT": (0x27, 0x4D, True),
    "SCREENSHOT": (0x7B, 0x58, False),  # F12 only
}


def pid_value(value):
    value = int(value)
    if value <= 0:
        raise argparse.ArgumentTypeError("PID must be positive")
    return value


def hold_value(value):
    value = float(value)
    if not 0.02 <= value <= 2.0:
        raise argparse.ArgumentTypeError("Hold duration must be 0.02 through 2.0 seconds")
    return value


class Win32:
    def __init__(self):
        if os.name != "nt":
            raise RuntimeError("This helper requires Windows")
        self.kernel = ctypes.WinDLL("kernel32", use_last_error=True)
        self.user = ctypes.WinDLL("user32", use_last_error=True)
        self.callback_type = ctypes.WINFUNCTYPE(wintypes.BOOL, wintypes.HWND, wintypes.LPARAM)
        self.kernel.OpenProcess.argtypes = [wintypes.DWORD, wintypes.BOOL, wintypes.DWORD]
        self.kernel.OpenProcess.restype = wintypes.HANDLE
        self.kernel.CloseHandle.argtypes = [wintypes.HANDLE]
        self.kernel.CloseHandle.restype = wintypes.BOOL
        self.kernel.QueryFullProcessImageNameW.argtypes = [wintypes.HANDLE, wintypes.DWORD, wintypes.LPWSTR, ctypes.POINTER(wintypes.DWORD)]
        self.kernel.QueryFullProcessImageNameW.restype = wintypes.BOOL
        self.kernel.GetExitCodeProcess.argtypes = [wintypes.HANDLE, ctypes.POINTER(wintypes.DWORD)]
        self.kernel.GetExitCodeProcess.restype = wintypes.BOOL
        self.user.EnumWindows.argtypes = [self.callback_type, wintypes.LPARAM]
        self.user.EnumWindows.restype = wintypes.BOOL
        self.user.GetWindowThreadProcessId.argtypes = [wintypes.HWND, ctypes.POINTER(wintypes.DWORD)]
        self.user.GetWindowThreadProcessId.restype = wintypes.DWORD
        self.user.GetWindowTextW.argtypes = [wintypes.HWND, wintypes.LPWSTR, ctypes.c_int]
        self.user.GetWindowTextW.restype = ctypes.c_int
        self.user.GetClassNameW.argtypes = [wintypes.HWND, wintypes.LPWSTR, ctypes.c_int]
        self.user.GetClassNameW.restype = ctypes.c_int
        self.user.IsWindowVisible.argtypes = [wintypes.HWND]
        self.user.IsWindowVisible.restype = wintypes.BOOL
        self.user.PostMessageW.argtypes = [wintypes.HWND, wintypes.UINT, wintypes.WPARAM, wintypes.LPARAM]
        self.user.PostMessageW.restype = wintypes.BOOL

    def open_verified(self, pid):
        # QUERY_LIMITED_INFORMATION only. No VM_READ/VM_WRITE or injection rights.
        handle = self.kernel.OpenProcess(0x1000, False, pid)
        if not handle:
            raise ctypes.WinError(ctypes.get_last_error())
        try:
            name = ctypes.create_unicode_buffer(32768)
            size = wintypes.DWORD(len(name))
            if not self.kernel.QueryFullProcessImageNameW(handle, 0, name, ctypes.byref(size)):
                raise ctypes.WinError(ctypes.get_last_error())
            if os.path.normcase(name.value) != os.path.normcase(EXPECTED_IMAGE):
                raise RuntimeError("PID executable is not the exact installed mGBA SDL executable")
            self.ensure_running(handle)
            return handle
        except BaseException:
            self.kernel.CloseHandle(handle)
            raise

    def ensure_running(self, handle):
        code = wintypes.DWORD()
        if not self.kernel.GetExitCodeProcess(handle, ctypes.byref(code)):
            raise ctypes.WinError(ctypes.get_last_error())
        if code.value != 259:  # STILL_ACTIVE
            raise RuntimeError("The verified process has exited")

    def windows(self, pid):
        result = []

        @self.callback_type
        def visit(hwnd, unused):
            owner = wintypes.DWORD()
            self.user.GetWindowThreadProcessId(hwnd, ctypes.byref(owner))
            if owner.value == pid:
                title = ctypes.create_unicode_buffer(1024)
                cls = ctypes.create_unicode_buffer(256)
                self.user.GetWindowTextW(hwnd, title, len(title))
                self.user.GetClassNameW(hwnd, cls, len(cls))
                result.append({"hwnd": hex(hwnd), "title": title.value,
                               "class": cls.value, "visible": bool(self.user.IsWindowVisible(hwnd))})
            return True

        if not self.user.EnumWindows(visit, 0):
            raise ctypes.WinError(ctypes.get_last_error())
        return result

    def ensure_window(self, pid, hwnd):
        owner = wintypes.DWORD()
        if not self.user.GetWindowThreadProcessId(hwnd, ctypes.byref(owner)) or owner.value != pid:
            raise RuntimeError("Window no longer belongs to the verified PID")

    def post_button(self, hwnd, virtual_key, scan_code, extended, release):
        # Fixed WM_KEYDOWN/WM_KEYUP only; no caller-supplied message IDs.
        flags = 1 | (scan_code << 16) | (int(extended) << 24)
        if release:
            flags |= (1 << 30) | (1 << 31)
        if not self.user.PostMessageW(hwnd, 0x0101 if release else 0x0100, virtual_key, flags):
            raise ctypes.WinError(ctypes.get_last_error())


def journal(record):
    JOURNAL.parent.mkdir(parents=True, exist_ok=True)
    with JOURNAL.open("a", encoding="utf-8") as stream:
        stream.write(json.dumps({"utc": datetime.now(timezone.utc).isoformat(), **record}) + "\n")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)
    listing = sub.add_parser("list", help="Read-only window enumeration for one verified PID")
    listing.add_argument("--pid", type=pid_value, required=True)
    press = sub.add_parser("press", help="Send one allowlisted button; runtime delivery remains UNVERIFIED")
    press.add_argument("--pid", type=pid_value, required=True)
    press.add_argument("--hwnd", type=lambda value: int(value, 0), help="Must be an enumerated visible SDL window of the requested PID")
    press.add_argument("button", choices=sorted(BUTTONS))
    press.add_argument("--hold", type=hold_value, default=0.08, help="Seconds, 0.02-2.0 (default 0.08)")
    args = parser.parse_args()
    api = Win32()
    handle = api.open_verified(args.pid)
    try:
        windows = api.windows(args.pid)
        if args.command == "list":
            print(json.dumps({"runtime_support": "UNVERIFIED", "pid": args.pid, "image": EXPECTED_IMAGE, "windows": windows}, indent=2))
            return 0
        candidates = [w for w in windows if w["visible"] and w["class"].startswith("SDL")]
        if args.hwnd is not None:
            candidates = [w for w in candidates if int(w["hwnd"], 0) == args.hwnd]
        if len(candidates) != 1:
            raise RuntimeError("Require exactly one visible SDL window; use list and --hwnd if ambiguous")
        hwnd = int(candidates[0]["hwnd"], 0)
        record = {"pid": args.pid, "hwnd": hex(hwnd), "button": args.button,
                  "hold_seconds": args.hold, "runtime_support": "UNVERIFIED"}
        journal({**record, "event": "attempt"})  # Refuse input if journaling fails.
        release_sent = False
        down_sent = False
        error = None
        try:
            api.ensure_running(handle)
            api.ensure_window(args.pid, hwnd)
            api.post_button(hwnd, *BUTTONS[args.button], release=False)
            down_sent = True
            time.sleep(args.hold)
        except BaseException as exc:
            error = exc
        finally:
            try:
                api.ensure_running(handle)
                api.ensure_window(args.pid, hwnd)
                api.post_button(hwnd, *BUTTONS[args.button], release=True)
                release_sent = True
            except BaseException as exc:
                if error is None:
                    error = exc
            journal({**record, "event": "outcome", "keydown_posted": down_sent,
                     "keyup_posted": release_sent, "error": str(error) if error else None,
                     "note": "Posting success does not prove SDL/game delivery; inspect screenshot"})
        if error is not None:
            raise error
        print(json.dumps({**record, "keydown_posted": down_sent, "keyup_posted": release_sent,
                          "journal": str(JOURNAL), "delivery": "UNVERIFIED"}))
        return 0
    finally:
        api.kernel.CloseHandle(handle)


if __name__ == "__main__":
    try:
        sys.exit(main())
    except (OSError, RuntimeError, ValueError) as exc:
        print(str(exc), file=sys.stderr)
        sys.exit(1)
