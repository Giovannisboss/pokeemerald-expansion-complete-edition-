"""Patch packaging tests use synthetic bytes; no retail ROM is needed."""
import hashlib
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

import bps
import package_release as release


class PackageTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(dir=Path(__file__).parent)
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.source = self.root / "clean.gba"
        self.target = self.root / "built.gba"
        self.output = self.root / "release"
        self.source.write_bytes(b"synthetic source for package testing")
        self.target.write_bytes(b"synthetic modified target with different size")
        # Substitute only the fixture digest in tests; production has no bypass option.
        self.digest = patch.object(bps, "CLEAN_SHA1", hashlib.sha1(self.source.read_bytes()).hexdigest())
        self.digest.start()
        self.addCleanup(self.digest.stop)

    def test_package_round_trip_manifest_and_checksums(self):
        source_before, target_before = self.source.read_bytes(), self.target.read_bytes()
        report = release.package_release(self.source, self.target, self.output)
        self.assertEqual({p.name for p in self.output.iterdir()}, {"CompleteEdition.bps", "release.json", "README.txt", "SHA256SUMS"})
        self.assertEqual(bps.apply(source_before, (self.output / "CompleteEdition.bps").read_bytes()), target_before)
        self.assertEqual(json.loads((self.output / "release.json").read_text()), report)
        self.assertEqual(report["target_sha256"], hashlib.sha256(target_before).hexdigest())
        for line in (self.output / "SHA256SUMS").read_text().splitlines():
            digest, name = line.split("  ")
            self.assertEqual(digest, hashlib.sha256((self.output / name).read_bytes()).hexdigest())
        self.assertEqual(self.source.read_bytes(), source_before)
        self.assertEqual(self.target.read_bytes(), target_before)
        self.assertFalse(list(self.root.glob(".ce-package-*")))

    def test_wrong_source_leaves_no_output(self):
        self.source.write_bytes(b"wrong input")
        with self.assertRaisesRegex(ValueError, "Expected clean Emerald"):
            release.package_release(self.source, self.target, self.output)
        self.assertFalse(self.output.exists())

    def test_empty_and_oversized_targets_leave_no_output(self):
        self.target.write_bytes(b"")
        with self.assertRaisesRegex(ValueError, "nonempty"):
            release.package_release(self.source, self.target, self.output)
        self.target.write_bytes(b"12345")
        with patch.object(release, "MAX_ROM_SIZE", 4), self.assertRaisesRegex(ValueError, "capacity"):
            release.package_release(self.source, self.target, self.output)
        self.assertFalse(self.output.exists())

    def test_existing_output_is_not_overwritten(self):
        self.output.mkdir()
        sentinel = self.output / "keep.txt"
        sentinel.write_text("preserve me")
        with self.assertRaisesRegex(ValueError, "already exists"):
            release.package_release(self.source, self.target, self.output)
        self.assertEqual(sentinel.read_text(), "preserve me")

    def test_round_trip_failure_leaves_no_output(self):
        with patch.object(bps, "apply", return_value=b"incorrect"), self.assertRaisesRegex(ValueError, "round-trip"):
            release.package_release(self.source, self.target, self.output)
        self.assertFalse(self.output.exists())

    def test_write_failure_cleans_staging_without_publishing_partial_package(self):
        write_bytes = Path.write_bytes
        def fail_manifest(path, data):
            if path.name == "release.json":
                raise OSError("simulated write failure")
            return write_bytes(path, data)
        with patch.object(Path, "write_bytes", fail_manifest), self.assertRaisesRegex(OSError, "simulated"):
            release.package_release(self.source, self.target, self.output)
        self.assertFalse(self.output.exists())
        self.assertFalse(list(self.root.glob(".ce-package-*")))


if __name__ == "__main__":
    unittest.main()
