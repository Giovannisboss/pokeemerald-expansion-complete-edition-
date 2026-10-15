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
    assert len(objects) <= 64, f"Too many NPCs: {path}"
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
assert count == 55, f"Expected 55 new service/leader/starter NPCs; found {count}"
print(f"Validated {count} new NPC placements: floor, elevation, adjacent access and event limits")

manifest = json.loads((root / "data/complete_edition_world.json").read_text())
assert len(manifest["leaders"]) == 24
assert len(manifest["starters"]) == 12
for kind in ("leaders", "starters"):
    for site in manifest[kind]:
        m = json.loads((root / "data/maps" / site["map"] / "map.json").read_text())
        assert "PokemonCenter" not in site["map"]
        matches = [o for o in m["object_events"] if o["script"] == site["script"]]
        assert len(matches) == 1
        assert all(matches[0][key] == site[key] for key in ("x", "y", "elevation"))
scripts = (root / "data/scripts/complete_edition_starters.inc").read_text()
for site in manifest["starters"]:
    block = scripts.split(site["script"] + "::", 1)[1].split("\n\n", 1)[0]
    assert f"setwildbattle SPECIES_{site['species']}, {site['level']}" in block
    assert block.index("B_OUTCOME_CAUGHT") < block.index("setflag " + site["flag"])
    assert f"FLAG_BADGE0{site['badges']}_GET" in block
research = (root / "data/scripts/complete_edition_research.inc").read_text()
assert "Script_CEGiveStarter" not in research
assert "CE_Visitor_" not in (root / "data/scripts/complete_edition_battles.inc").read_text()
# Route 101 introduces Kanto, Johto and Sinnoh species before the first badge.
wild = json.loads((root / "src/data/wild_encounters.json").read_text())["wild_encounter_groups"][0]["encounters"]
r101 = next(e for e in wild if e["map"] == "MAP_ROUTE101")
assert {"SPECIES_PIDGEY", "SPECIES_SENTRET", "SPECIES_STARLY", "SPECIES_BIDOOF"} <= {m["species"] for m in r101["land_mons"]["mons"]}
print("Validated 24 independent leader battles, 12 capture-only starter flags and early multi-generation encounters")

assert "goto_if_unset FLAG_BADGE07_GET, CE_Research_NeedMindBadge" in research
assert "FLAG_SYS_GAME_CLEAR" not in research
assert "FlagGet(FLAG_BADGE07_GET)" in (root / "src/complete_edition_research.c").read_text()
print("Validated matching seventh-badge catalogue gates in script and native encounter creation")
