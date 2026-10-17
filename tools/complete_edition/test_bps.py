"""Release patch integrity checks using synthetic bytes only."""
import random
import struct
import unittest
import zlib

import bps


def raw_patch(source, target_size, commands=b"", metadata=b"", target=b""):
    data = (b"BPS1" + bps.number(len(source)) + bps.number(target_size)
            + bps.number(len(metadata)) + metadata + commands)
    data += struct.pack("<II", zlib.crc32(source), zlib.crc32(target))
    return data + struct.pack("<I", zlib.crc32(data))


class BpsTests(unittest.TestCase):
    def test_round_trips(self):
        rng = random.Random(493)
        pairs = [(b"", b""), (b"", b"new"), (b"old", b""),
                 (b"same", b"same"), (b"abcdefghij", b"Xbcdefghij")]
        for _ in range(100):
            source = rng.randbytes(rng.randrange(256))
            target = bytearray(source[:rng.randrange(len(source) + 1)])
            target += rng.randbytes(rng.randrange(40))
            pairs.append((source, bytes(target)))
        for source, target in pairs:
            with self.subTest(source_size=len(source), target_size=len(target)):
                self.assertEqual(bps.apply(source, bps.create(source, target)), target)

    def test_short_and_corrupt_patches(self):
        patch = bps.create(b"source", b"target")
        for size in range(len(patch)):
            with self.subTest(size=size), self.assertRaises(ValueError):
                bps.apply(b"source", patch[:size])
        corrupt = bytearray(patch)
        corrupt[5] ^= 1
        with self.assertRaises(ValueError):
            bps.apply(b"source", corrupt)

    def test_wrong_source(self):
        with self.assertRaisesRegex(ValueError, "Wrong input ROM"):
            bps.apply(b"wrong!", bps.create(b"source", b"target"))

    def test_command_boundaries(self):
        cases = [
            (b"", 1, b"", "Truncated BPS number"),
            (b"", 1, b"\x00", "Truncated BPS number"),
            (b"", 1, bytes(bps.number(0)), "SourceRead exceeds"),
            (b"a", 2, bytes(bps.number(4)), "SourceRead exceeds"),
            (b"a", 1, bytes(bps.number(4)), "exceeds target size"),
            (b"", 1, bytes(bps.number(1)), "Truncated BPS TargetRead"),
            (b"", 1, bytes(bps.number(2)), "SourceRead/TargetRead"),
        ]
        for source, size, commands, error in cases:
            with self.subTest(error=error), self.assertRaisesRegex(ValueError, error):
                bps.apply(source, raw_patch(source, size, commands))

    def test_metadata_cannot_consume_checksums(self):
        data = b"BPS1" + bps.number(0) + bps.number(0) + bps.number(1)
        data += struct.pack("<II", 0, 0)
        patch = data + struct.pack("<I", zlib.crc32(data))
        with self.assertRaisesRegex(ValueError, "Truncated BPS metadata"):
            bps.apply(b"", patch)

    def test_target_crc_and_trailing_commands(self):
        with self.assertRaisesRegex(ValueError, "Target checksum mismatch"):
            bps.apply(b"", raw_patch(b"", 1, bps.number(1) + b"a", target=b"b"))
        with self.assertRaisesRegex(ValueError, "Target checksum mismatch"):
            bps.apply(b"", raw_patch(b"", 0, b"\x80"))


if __name__ == "__main__":
    unittest.main()
