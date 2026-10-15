#!/usr/bin/env python3
"""Plan conservative foot routes for the button-only QA controller.

Static tiles and NPC origins cannot predict moving NPCs or trainer sight lines.
Check the live position after every segment and replan after interruptions.
"""
import argparse
import heapq
import itertools
import json

from map_tiles import ROOT, MapTiles, STABLE_GROUND

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('map')
parser.add_argument('start_x', type=int)
parser.add_argument('start_y', type=int)
parser.add_argument('goal_x', type=int)
parser.add_argument('goal_y', type=int)
parser.add_argument('--elevation', type=int, default=3)
parser.add_argument('--blocked', action='append', default=[], help='additional live NPC x,y')
args = parser.parse_args()
game_map = json.loads((ROOT / 'data/maps' / args.map / 'map.json').read_text())
tiles = MapTiles(game_map)
blocked = {(obj['x'], obj['y']) for obj in game_map['object_events']}
blocked.update(tuple(map(int, item.split(','))) for item in args.blocked)
start = (args.start_x, args.start_y)
goal = (args.goal_x, args.goal_y)
queue = [(0, start, [])]
visited = set()
while queue:
    cost, pos, path = heapq.heappop(queue)
    if pos in visited:
        continue
    visited.add(pos)
    if pos == goal:
        groups = [(key, len(list(run))) for key, run in itertools.groupby(path)]
        print(json.dumps({'start': start, 'goal': goal, 'key_tiles': groups}))
        break
    for dx, dy, key in [(1, 0, 16), (-1, 0, 32), (0, 1, 128), (0, -1, 64)]:
        target = (pos[0] + dx, pos[1] + dy)
        collision, elevation, behavior = tiles.tile(*target)
        if (collision == 0 and elevation in (0, args.elevation)
                and (behavior in STABLE_GROUND or 'BRIDGE' in behavior)
                and target not in blocked and target not in visited):
            heapq.heappush(queue, (cost + (10 if 'GRASS' in behavior else 1), target, path + [key]))
else:
    raise SystemExit('No conservative foot route; inspect elevation, dynamic NPCs, warps or special terrain.')
