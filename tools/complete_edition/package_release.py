#!/usr/bin/env python3
"""Build a verified patch-only development package using your own clean ROM."""
import argparse
import hashlib
import json
from pathlib import Path
import tempfile

import bps

MAX_ROM_SIZE = 32 * 1024 * 1024


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def package_release(source_path, target_path, output):
    output = Path(output)
    if output.exists() or output.is_symlink():
        raise ValueError("Output directory already exists; choose a new directory")
    source = Path(source_path).read_bytes()
    target = Path(target_path).read_bytes()
    if hashlib.sha1(source).hexdigest() != bps.CLEAN_SHA1:
        raise ValueError("Expected clean Emerald US/EU revision 0 (SHA-1 " + bps.CLEAN_SHA1 + ")")
    if not target or len(target) > MAX_ROM_SIZE:
        raise ValueError("Target must be nonempty and within standard GBA ROM capacity")
    patch = bps.create(source, target)
    if bps.apply(source, patch) != target:
        raise ValueError("Patch round-trip verification failed")
    manifest = {
        "name": "Pokemon Emerald: Complete Edition",
        "status": "development; final release verification incomplete",
        "save_format": "Alpha 2; incompatible with Alpha 1 and original Emerald saves",
        "source_sha1": bps.CLEAN_SHA1,
        "target_sha256": sha256(target),
        "target_size_bytes": len(target),
        "patch_sha256": sha256(patch),
        "verification": "BPS CRCs and exact apply-to-clean-ROM round trip; does not certify gameplay",
        "remaining": ["ordinary story and postgame certification", "hardware verification"],
    }
    readme = (
        "Pokemon Emerald: Complete Edition - development patch\n\n"
        "Apply CompleteEdition.bps to your own clean Emerald US/EU revision-0 ROM\n"
        "using a BPS-compatible patcher. The required source SHA-1 is:\n"
        + bps.CLEAN_SHA1 + "\n\n"
        "Confirm that the patched ROM SHA-256 matches target_sha256 in release.json.\n"
        "This package contains neither the clean ROM nor the compiled ROM.\n\n"
        "Back up your battery save before upgrading. Alpha 2 saves are supported;\n"
        "Alpha 1 and original Emerald saves are incompatible. Keep old ROM/save\n"
        "pairs together. Copy a supported battery save beside the patched ROM\n"
        "using its basename and the .sav extension. Load Continue, not a savestate.\n\n"
        "This is a development build. Ordinary story/postgame certification,\n"
        "and hardware verification remain unfinished.\n"
        "Patch verification alone is not game-completion certification.\n"
        "Consult the native verification logs for known failures, skips and TODOs.\n"
    )
    files = {
        "CompleteEdition.bps": patch,
        "release.json": (json.dumps(manifest, indent=2) + "\n").encode("utf-8"),
        "README.txt": readme.encode("utf-8"),
    }
    files["SHA256SUMS"] = "".join(sha256(data) + "  " + name + "\n" for name, data in sorted(files.items())).encode("ascii")
    output.parent.mkdir(parents=True, exist_ok=True)
    # Stage beside the destination; publish only after every file is complete.
    with tempfile.TemporaryDirectory(prefix=".ce-package-", dir=output.parent) as temporary:
        staged = Path(temporary) / "package"
        staged.mkdir()
        for name, data in files.items():
            (staged / name).write_bytes(data)
        staged.rename(output)
    return manifest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path)
    parser.add_argument("target", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()
    try:
        manifest = package_release(args.source, args.target, args.output)
    except (OSError, ValueError) as error:
        parser.error(str(error))
    print("Verified patch-only package:", args.output)
    print("Patched ROM SHA-256:", manifest["target_sha256"])


if __name__ == "__main__":
    main()
