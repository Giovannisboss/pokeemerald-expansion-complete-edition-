#!/usr/bin/env python3
"""Export Hoenn's ordinary wild tables as a player-searchable CSV."""
import argparse
import csv
import json
import re
from pathlib import Path

root = Path(__file__).resolve().parents[2]


def export(destination):
    group = json.loads((root / "src/data/wild_encounters.json").read_text())["wild_encounter_groups"][0]
    maps = {}
    for path in (root / "data/maps").glob("*/map.json"):
        if "Frlg" in path.parent.name or "Unused" in path.parent.name or "Prototype" in path.parent.name:
            continue
        info = json.loads(path.read_text())
        maps[info["id"]] = info["name"]
    fields = {field["type"]: field for field in group["fields"]}
    with destination.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle)
        writer.writerow(["Area", "Method", "Pokemon", "Chance percent", "Min level", "Max level", "Table variant"])
        for entry in group["encounters"]:
            if entry["map"] not in maps:
                continue
            name = re.sub(r"([a-z])([A-Z0-9])", r"\1 \2", maps[entry["map"]]).replace("_", " ")
            for field_name, field in fields.items():
                if field_name not in entry:
                    continue
                slots = entry[field_name]["mons"]
                methods = field.get("groups", {field_name.removesuffix("_mons"): list(range(len(slots)))})
                for method, indices in methods.items():
                    species = {}
                    for index in indices:
                        mon = slots[index]
                        values = species.setdefault(mon["species"], [0, 100, 1])
                        values[0] += field["encounter_rates"][index]
                        values[1] = min(values[1], mon["min_level"])
                        values[2] = max(values[2], mon["max_level"])
                    for pokemon, values in species.items():
                        writer.writerow([name, method.replace("_", " ").title(), pokemon.removeprefix("SPECIES_").replace("_", " ").title(), *values, entry["base_label"]])


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("destination", type=Path)
    export(parser.parse_args().destination)
