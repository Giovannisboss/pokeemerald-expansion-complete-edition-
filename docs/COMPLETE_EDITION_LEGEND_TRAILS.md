# Legendary trails — Alpha 2.2 development build

The researcher in Birch's lab now offers **Legendary trails** hints from the start of the game. Each new trail requires the Mind Badge. Stronger encounters also require entry to the Hall of Fame. These are fixed wild battles using your own Poké Balls. Defeat, fleeing or losing does not consume an encounter; only capture completes its trail. The catalogue continues to unlock after the seventh Gym.

The original Regirock, Regice, Registeel, Kyogre, Groudon and Rayquaza events remain unchanged. Together with the 29 new trails below, all 35 legendary/mythical species from Generations 1–4 have world encounters. Catalogue captures do not count as completion of a linked world trail.

| Pokémon | Location | Level | Additional requirements |
| --- | --- | ---: | --- |
| Articuno | Shoal Cave — low-tide ice room | 50 | Mind Badge only |
| Zapdos | New Mauville | 50 | Mind Badge only |
| Moltres | Mt. Chimney | 50 | Mind Badge only |
| Mewtwo | Desert Underpass | 70 | Hall of Fame |
| Mew | Petalburg Woods | 50 | Complete Celebi trails |
| Raikou | Route 118 | 50 | Mind Badge only |
| Entei | Fiery Path | 50 | Mind Badge only |
| Suicune | Route 119 | 50 | Mind Badge only |
| Lugia | Abandoned Ship — hidden-floor rooms | 70 | Hall of Fame; Complete Articuno, Zapdos, Moltres trails |
| Ho-Oh | Mt. Pyre summit | 70 | Hall of Fame; Complete Raikou, Entei, Suicune trails |
| Celebi | Route 120 | 50 | Mind Badge only |
| Latias | Route 123 | 50 | Mind Badge only |
| Latios | Route 115 | 50 | Mind Badge only |
| Jirachi | Meteor Falls — entrance chamber | 50 | Mind Badge only |
| Deoxys | Mossdeep City | 70 | Hall of Fame |
| Uxie | Safari Zone — northwest area | 50 | Mind Badge only |
| Mesprit | Route 114 | 50 | Mind Badge only |
| Azelf | Route 120 | 50 | Mind Badge only |
| Dialga | Sky Pillar — first floor | 70 | Hall of Fame; Complete Uxie, Mesprit, Azelf trails |
| Palkia | Seafloor Cavern — final chamber | 70 | Hall of Fame; Complete Uxie, Mesprit, Azelf trails |
| Heatran | Fiery Path | 70 | Hall of Fame |
| Regigigas | Ancient Tomb | 70 | Hall of Fame; Regirock, Regice and Registeel in the party; Eggs do not count |
| Giratina | Mt. Pyre — sixth floor | 75 | Hall of Fame; Complete Dialga, Palkia trails |
| Cresselia | Route 125 | 60 | Hall of Fame |
| Phione | Route 109 | 50 | Mind Badge only |
| Manaphy | Route 105 | 50 | Mind Badge only |
| Darkrai | Mt. Pyre — fourth floor | 70 | Hall of Fame |
| Shaymin | Route 117 | 50 | Mind Badge only |
| Arceus | Sky Pillar summit | 80 | Hall of Fame; Complete Giratina, Mew, Celebi, Jirachi, Manaphy, Darkrai, Shaymin trails |

Encounter coordinates and quest dependencies are recorded in `data/complete_edition_world.json`. Regenerate authored map objects, scripts and native data using `python3 tools/complete_edition/generate_legends.py`.

**QA status:** compiled; native checks pass for all 29 encounter factories, badge/Champion gates, quest prerequisites, Regi party requirements, hints and flash-persistent completion flags. The hint menu and pre-badge catalogue refusal were exercised through ordinary input in the production ROM. Full normal-play travel, event capture interactions and balance remain open. This guide is not a release certification.
