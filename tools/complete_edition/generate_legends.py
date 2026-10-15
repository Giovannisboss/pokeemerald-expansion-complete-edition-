#!/usr/bin/env python3
"""Regenerate the authored legendary trails; coordinates live in the world manifest."""
import json
from pathlib import Path
import re
import textwrap

def write_if_changed(path, text):
    if not path.exists() or path.read_text() != text:
        path.write_text(text)


root = Path(__file__).resolve().parents[2]
world = json.loads((root / 'data/complete_edition_world.json').read_text())
sites = world['legends']
assert len(sites) == 29
ids = {s['species']: s['id'] for s in sites}
assert sorted(ids.values()) == list(range(29))
flags_path = root / 'include/constants/flags.h'
flags = flags_path.read_text()
blocks = []
records = []
maps = {}

def game_text(label, paragraphs):
    wrapped = ['\\n'.join(textwrap.wrap(p, width=34)) for p in paragraphs]
    return label + ':\n\t.string "' + '\\p'.join(wrapped) + '$"\n'

for site in sites:
    name = site['species']
    ident = site['id']
    old = rf'^#define (?:FLAG_UNUSED_0x{0x2c + ident:03X}|{site["flag"]})\s+0x{0x2c + ident:X}[^\n]*$'
    flags, count = re.subn(old, f'#define {site["flag"]:<38} 0x{0x2c + ident:X} // Complete Edition legendary trail', flags, flags=re.M)
    assert count == 1, f'Flag not available for {name}'
    path = root / 'data/maps' / site['map'] / 'map.json'
    game_map = maps.setdefault(path, json.loads(path.read_text()))
    obj = dict(graphics_id=f'OBJ_EVENT_GFX_SPECIES_SHINY({name})', x=site['x'], y=site['y'], elevation=site['elevation'], movement_type='MOVEMENT_TYPE_FACE_DOWN', movement_range_x=0, movement_range_y=0, trainer_type='TRAINER_TYPE_NONE', trainer_sight_or_berry_tree_id='0', script=site['script'], flag=site['flag'])
    game_map['object_events'] = [o for o in game_map['object_events'] if o.get('script') != site['script']] + [obj]
    mask = sum(1 << ids[species] for species in site['requires'])
    records.append(f'    [{ident}] = {{SPECIES_{name}, {site["flag"]}, {site["level"]}, {str(site["champion"]).upper()}, {str(site["regis_party"]).upper()}, 0x{mask:08X}}},')
    label = site['script']
    blocks.append(f'''{label}::
\tlock
\tfaceplayer
\tsetvar VAR_0x8005, {ident}
\tcallnative Script_CELegendIsReady
\tgoto_if_eq VAR_RESULT, FALSE, {label}_NotReady
\tmsgbox {label}_Text, MSGBOX_YESNO
\tgoto_if_eq VAR_RESULT, NO, CE_Legend_End
\tsetvar VAR_0x8005, {ident}
\tcallnative Script_CEPrepareLegend
\tgoto_if_eq VAR_RESULT, FALSE, CE_Legend_End
\tplaymoncry SPECIES_{name}, CRY_MODE_ENCOUNTER
\twaitmoncry
\tdowildbattle
\tspecialvar VAR_RESULT, GetBattleOutcome
\tgoto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
\tsetflag {site['flag']}
\tremoveobject VAR_LAST_TALKED
\tgoto CE_Legend_End

{label}_NotReady:
\tmsgbox {label}_Locked, MSGBOX_DEFAULT
\tgoto CE_Legend_End
''')
    requirements = ['Earn the MIND BADGE.']
    if site['champion']:
        requirements.append('Enter the HALL OF FAME.')
    if site['requires']:
        requirements.append('Complete the Hoenn trails of ' + ', '.join(n.replace('_', '-') for n in site['requires']) + '.')
    if site['regis_party']:
        requirements.append('Bring REGIROCK, REGICE and REGISTEEL together in your party.')
    blocks.append(game_text(label + '_Text', [site['lore'], f'A shiny {name.replace("_", "-")} waits. Challenge it?']))
    blocks.append(game_text(label + '_Locked', ['It is waiting for a worthy visitor.'] + requirements))
    blocks.append(game_text(label + '_Hint', [site['hint'] + '.'] + requirements))

for path, game_map in maps.items():
    write_if_changed(path, json.dumps(game_map, indent=2) + '\n')

write_if_changed(root / 'data/scripts/complete_edition_legends.inc', '// Generated from data/complete_edition_world.json.\n\n' + '\n'.join(blocks) + '\nCE_Legend_End:\n\trelease\n\tend\n')
write_if_changed(root / 'src/data/complete_edition_legends.h', '// Generated from data/complete_edition_world.json.\nconst struct CELegend gCELegends[CE_LEGEND_COUNT] =\n{\n' + '\n'.join(records) + '\n};\n')
write_if_changed(flags_path, flags)
# A cancel-safe field guide is available before any trail unlocks.
menu = ['CE_Legend_Hints::', '\tcallnative Script_CELegendHintsMenu', '\tdynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL']
for s in sites:
    menu.append(f'\tgoto_if_eq VAR_RESULT, {s["id"] + 1024}, {s["script"]}_ShowHint')
menu.append('\tgoto CE_Research_End')
for s in sites:
    menu += [f'{s["script"]}_ShowHint:', f'\tmsgbox {s["script"]}_Hint, MSGBOX_DEFAULT', '\tgoto CE_Research_End']
write_if_changed(root / 'data/scripts/complete_edition_legend_hints.inc', '// Generated legendary trail guide.\n' + '\n'.join(menu) + '\n')
print('Generated 29 catch-only legendary trails and their in-game hints')
