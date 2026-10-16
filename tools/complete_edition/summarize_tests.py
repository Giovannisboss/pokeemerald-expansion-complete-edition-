#!/usr/bin/env python3
"""Summarize native emulator output without treating partial runs as complete."""
import argparse
from collections import Counter
import json
from pathlib import Path
import re

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("log", type=Path)
args = parser.parse_args()
raw_lines = args.log.read_text(errors="replace").splitlines()
lines = [re.sub(r"\x1b\[[0-9;]*m", "", line) for line in raw_lines]
counts = Counter()
failures = []
completed_total = None
accepted_statuses = {"PASS", "EXPECTED_FAIL", "KNOWN_FAILING", "ASSUMPTION_FAIL", "TO_DO"}
known_failures = []
expected_crashes = 0
footer_failures = 0
for index, line in enumerate(lines):
    result = re.match(r"^\[\d+\] (.*): ([A-Z_]+)$", line)
    if result:
        name, status = result.groups()
        counts[status] += 1
        # The native runner colors EXPECT_CRASH green and unexpected crashes red.
        # Colorless crashes are ambiguous, so fail closed rather than hide a crash.
        expected_crash = status == "CRASH" and raw_lines[index].endswith("\x1b[32mCRASH\x1b[0m")
        if expected_crash:
            expected_crashes += 1
        if status == "KNOWN_FAILING":
            known_failures.append({"name": name, "detail": lines[index + 1] if index + 1 < len(lines) else ""})
        if status not in accepted_statuses and not expected_crash:
            detail = lines[index + 1] if index + 1 < len(lines) else ""
            failures.append({"name": name, "status": status, "detail": detail})
    footer_failure = re.match(r"^- (?:Tests FAILED|EXPECTED_FAIL_PASSING):\s+(\d+)", line)
    if footer_failure:
        footer_failures += int(footer_failure[1])
    total = re.match(r"^- Tests TOTAL:\s+(\d+)", line)
    if total:
        completed_total = int(total[1])

recorded = sum(counts.values())
complete = completed_total is not None and recorded == completed_total
json.dump({
    "log": str(args.log),
    "complete": complete,
    "recorded_results": recorded,
    "reported_total": completed_total,
    "statuses": dict(sorted(counts.items())),
    "failing_outcomes": len(failures),
    "expected_crashes": expected_crashes,
    "footer_failures": footer_failures,
    "known_failures": known_failures,
    "no_failing_outcomes": complete and bool(recorded) and not failures and not footer_failures,
    "failures": failures,
}, __import__("sys").stdout, indent=2)
print()
