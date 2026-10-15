"""Read Emerald metatile behaviors for placement and travel validation."""
import json
from pathlib import Path
import re
import struct

ROOT = Path(__file__).resolve().parents[2]
_headers = (ROOT / 'src/data/tilesets/headers.h').read_text()
_attributes = (ROOT / 'src/data/tilesets/metatiles.h').read_text()
BEHAVIORS = re.findall(r'^\s*(MB_\w+)\s*,', (ROOT / 'include/constants/metatile_behaviors.h').read_text(), re.M)
LAYOUTS = {e['id']: e for e in json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts']}

# Static encounters need a place where the player can stop and interact.
STABLE_GROUND = {'MB_NORMAL', 'MB_TALL_GRASS', 'MB_LONG_GRASS', 'MB_SHORT_GRASS',
                 'MB_CAVE', 'MB_NO_RUNNING', 'MB_INDOOR_ENCOUNTER',
                 'MB_MOUNTAIN_TOP', 'MB_SAND', 'MB_DEEP_SAND',
                 'MB_ASHGRASS', 'MB_FOOTPRINTS', 'MB_PUDDLE', 'MB_SHALLOW_WATER'}


def attribute_data(tileset):
    block = re.search(r'const struct Tileset ' + re.escape(tileset) + r'\s*=\s*\{(.*?)\};', _headers, re.S)
    name = re.search(r'\.metatileAttributes\s*=\s*(\w+)', block[1])[1]
    path = re.search(r'const u16 ' + re.escape(name) + r'\[\]\s*=\s*INCBIN_U16\("([^"]+)"\)', _attributes)[1]
    return (ROOT / path).read_bytes()


class MapTiles:
    def __init__(self, game_map):
        self.layout = LAYOUTS[game_map['layout']]
        self.width = self.layout['width']
        self.height = self.layout['height']
        self.blocks = (ROOT / self.layout['blockdata_filepath']).read_bytes()
        self.primary = attribute_data(self.layout['primary_tileset'])
        self.secondary = attribute_data(self.layout['secondary_tileset'])

    def tile(self, x, y):
        if not 0 <= x < self.width or not 0 <= y < self.height:
            return 3, 0, 'OUT_OF_BOUNDS'
        value = struct.unpack_from('<H', self.blocks, 2 * (y * self.width + x))[0]
        metatile = value & 0x3ff
        data = self.primary if metatile < 512 else self.secondary
        offset = metatile if metatile < 512 else metatile - 512
        behavior = struct.unpack_from('<H', data, 2 * offset)[0] & 0xff
        return (value >> 10) & 3, value >> 12, BEHAVIORS[behavior]
