#!/usr/bin/env python3
"""Reject truncated compiler outputs left by interrupted builds."""
import argparse
import struct
from pathlib import Path

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("profile", choices=("emerald", "emerald-test"))
parser.add_argument("--repair", action="store_true", help="remove invalid generated objects so make rebuilds them")
args = parser.parse_args()
root = Path(__file__).resolve().parents[2]
build = root / "build" / args.profile
invalid = []
count = 0
for path in sorted(build.rglob("*.o")):
    count += 1
    with path.open("rb") as stream:
        header = stream.read(52)
    # Every target object, including objects without code, is an ARM ELF file.
    valid = len(header) == 52 and header[:6] == b"\x7fELF\x01\x01" and header[16:20] == b"\x01\x00\x28\x00"
    if valid:
        section_offset = struct.unpack_from("<I", header, 32)[0]
        section_size, section_count = struct.unpack_from("<HH", header, 46)
        valid = section_size >= 40 and section_count > 0 and section_offset + section_size * section_count <= path.stat().st_size
    if not valid:
        invalid.append(path)
        print(f"Invalid generated object: {path.relative_to(build)}")
        if args.repair:
            path.unlink()
expected = []
for source_dir in (["src", "test"] if args.profile == "emerald-test" else ["src"]):
    for pattern in ("*.c", "*/*.c", "*/*/*.c"):
        expected.extend(build / path.relative_to(root).with_suffix(".o")
                        for path in (root / source_dir).glob(pattern)
                        if not path.name.endswith(".inc.c"))
missing = [path for path in expected if not path.is_file()]
if missing:
    print(f"{len(missing)} source object(s) {'scheduled for compilation' if args.repair else 'missing'} in {args.profile}")
if invalid:
    print(f"{'Removed' if args.repair else 'Rejected'} {len(invalid)} invalid object(s) in {args.profile}")
    raise SystemExit(0 if args.repair else 1)
if missing and not args.repair:
    raise SystemExit(1)
print(f"Validated {count} ARM ELF object headers in {args.profile}")
