#!/usr/bin/env python3
"""Check reachability and event limits of every added Complete Edition NPC."""
import json
import struct
from pathlib import Path

root = Path(__file__).resolve().parents[2]
layouts = {entry["id"]: entry for entry in json.loads((root / "data/layouts/layouts.json").read_text())["layouts"]}
count = 0
for path in sorted((root / "data/maps").glob("*/map.json")):
    game_map = json.loads(path.read_text())
    objects = game_map.get("object_events", [])
    added = [obj for obj in objects if str(obj.get("script", "")).startswith("CE_")]
    if not added:
        continue
    assert len(objects) <= 16, f"Too many NPCs: {path}"
    layout = layouts[game_map["layout"]]
    data = (root / layout["blockdata_filepath"]).read_bytes()
    width, height = layout["width"], layout["height"]

    def tile(x, y):
        if not 0 <= x < width or not 0 <= y < height:
            return 3, 0
        value = struct.unpack_from("<H", data, 2 * (y * width + x))[0]
        return (value >> 10) & 3, value >> 12

    for obj in added:
        x, y = obj["x"], obj["y"]
        collision, elevation = tile(x, y)
        assert collision == 0, f"NPC placed on solid tile: {path} {obj['script']}"
        assert obj["elevation"] in (0, elevation), f"Wrong NPC elevation: {path}"
        assert any(tile(x + dx, y + dy)[0] == 0 for dx, dy in [(1, 0), (-1, 0), (0, 1), (0, -1)]), f"Inaccessible NPC: {path}"
        assert sum(other.get("x") == x and other.get("y") == y for other in objects) == 1, f"Overlapping NPC: {path}"
        count += 1
assert count == 27, f"Expected 27 new service/visitor NPCs; found {count}"
print(f"Validated {count} new NPC placements: floor, elevation, adjacent access and event limits")
