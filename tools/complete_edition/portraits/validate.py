"""Validate CE portrait source wiring and optional actual 64x64 indexed artwork."""
import argparse
import json
import re
from pathlib import Path

parser = argparse.ArgumentParser()
parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parent)
parser.add_argument("--assets-root", type=Path)
parser.add_argument("--source-only", action="store_true")
args = parser.parse_args()
manifest = json.loads((Path(__file__).resolve().parent / "manifest.json").read_text())
root = args.root
ids_source = (root / "include/constants/trainers.h").read_text()
gfx = (root / "src/data/graphics/trainers.h").read_text()
party = (root / "src/data/trainers.party").read_text()
enum = ids_source.split("enum __attribute__((packed)) TrainerPicID", 1)[1].split("};", 1)[0]
ids = re.findall(r"TRAINER_PIC_[A-Z0-9_]+", enum)
old_ids = manifest["original_pic_ids"]
assert ids[:len(old_ids)] == old_ids, "Existing trainer portrait IDs changed"
assert ids[-1] == "TRAINER_PIC_COUNT"
assert len(ids) - 1 < 256, "Packed trainer picture enum overflow"
assert len(ids) - 1 == len(old_ids) + 18
blocks = re.split(r"(?=^=== )", party, flags=re.M)
counts = {p["pic"]: 0 for p in manifest["portraits"]}
for p in manifest["portraits"]:
    assert ids.count(p["id"]) == 1, p["id"]
    stem = "".join(x.capitalize() for x in p["path"].split("ce_", 1)[1].split(".")[0].split("_"))
    pic_array = "gTrainerFrontPic_CE" + stem
    pal_array = "gTrainerPalette_CE" + stem
    assert f'const u32 {pic_array}[] = INCGFX_U32("{p["path"]}", ".4bpp.smol");' in gfx
    assert f'const u16 {pal_array}[] = INCGFX_U16("{p["path"]}", ".gbapal");' in gfx
    expected = rf'\[{p["id"]}\]\s*=\s*\{{\s*\.frontPic\s*=\s*TRAINER_FRONT_PIC\({pic_array}, {pal_array}\),\s*\}},'
    assert re.search(expected, gfx), p["id"]
for block in blocks:
    pic = re.search(r"^Pic: (.+)$", block, flags=re.M)
    if pic and pic[1] in counts:
        assert block.startswith("=== TRAINER_CE_"), "CE artwork changed another trainer"
        counts[pic[1]] += 1
assert sum(counts.values()) == manifest["expected_picture_replacements"]
for pic, count in counts.items():
    assert count == (1 if pic in {"CE Gold", "CE Silver"} else 2), (pic, count)
print(f"PASS: 18 unique portrait IDs and graphics mappings; 34 trainer assignments; {len(old_ids)} old IDs preserved")
if not args.source_only:
    from PIL import Image
    assets = args.assets_root or root
    hashes = set()
    import hashlib
    for p in manifest["portraits"]:
        path = assets / p["path"]
        with Image.open(path) as im:
            assert im.format == "PNG" and im.size == (64, 64), (path, im.size)
            assert im.mode == "P", (path, im.mode)
            used = im.getcolors(4096)
            assert used and max(index for _, index in used) < 16, path
            assert im.info.get("transparency") == 0, (path, im.info.get("transparency"))
            digest = hashlib.sha256(im.convert("RGBA").tobytes()).hexdigest()
            assert digest not in hashes, f"Duplicate artwork: {path}"
            hashes.add(digest)
    print("PASS: 18 distinct indexed 64x64 PNGs, <=16 indexed colors, transparent palette slot 0")
else:
    print("Artwork not checked (--source-only); completion requires PNG validation and battle visual review.")

