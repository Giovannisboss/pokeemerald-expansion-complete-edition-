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
lines = re.sub(r"\x1b\[[0-9;]*m", "", args.log.read_text(errors="replace")).splitlines()
counts = Counter()
failures = []
completed_total = None
failure_statuses = {"FAIL", "FLAKY", "TIMEOUT", "INVALID", "ERROR"}
for index, line in enumerate(lines):
    result = re.match(r"^\[\d+\] (.*): ([A-Z_]+)$", line)
    if result:
        name, status = result.groups()
        counts[status] += 1
        if status in failure_statuses:
            detail = lines[index + 1] if index + 1 < len(lines) else ""
            failures.append({"name": name, "status": status, "detail": detail})
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
    "no_failing_outcomes": complete and bool(recorded) and not failures,
    "failures": failures,
}, __import__("sys").stdout, indent=2)
print()
