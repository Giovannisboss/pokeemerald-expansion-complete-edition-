# Pokémon Emerald: Complete Edition

Fan-made ROM hack built on RHH pokeemerald-expansion.

## Design target
- Original Hoenn adventure and Battle Frontier retained where practical.
- National Pokédex species #1–493 obtainable in one save, without trading.
- Every Pokémon shiny, including wild, gift, egg, static and trainer Pokémon.
- Generation 4 physical/special move split and Gen 1–4 mechanics; no Fairy type.
- Steven replaces Wallace as Champion; moderate main-story difficulty.
- Birch's research catalogue unlocks after the seventh Gym (Mind Badge), retaining its level-50 catchable encounters and existing menus.
- All starter families obtainable; all Gen 1–4 legendary and mythical Pokémon obtainable through events.
- 24 optional visiting Gym Leaders from Kanto, Johto and Sinnoh, plus postgame World Tournament with all 32 regional leaders.
- Postgame superbosses Red, Blue, Silver and Gold with competitive teams.
- Pokémon Centre nature-changing service, Bottle Caps for IVs, and EV reset/allocation service.
- Original Battle Frontier preserved; GBA-friendly Complete Edition title screen.

## Engineering principles
1. Implement and verify one milestone at a time; do not claim planned features are working.
2. Keep the upstream engine attribution and copyright notices.
3. Never commit the original retail ROM or proprietary game dumps.
4. Develop on a dedicated branch; compile and test before merging.
5. Keep Gen 1–4 availability and the physical/special split independent from the engine's newer-generation defaults.

## Milestones
- [x] Fork connected; development branch created.
- [x] Establish reproducible Codespaces build and baseline ROM test.
- [x] Configure species, types, moves and battle mechanics.
- [x] Implement and test universal shiny generation, including trainers.
- [x] Build encounter, evolution, starter and legendary availability.
- [x] Implement trainer difficulty and Steven Champion battle.
- [x] Add nature/IV/EV services.
- [x] Add visiting Gym Leaders and World Tournament.
- [x] Add postgame superbosses.
- [x] Adapt title art to GBA hardware constraints.
- [ ] Regression-test story, saves, Battle Frontier and final patch.

**Status:** Alpha 2.3 fixes Gen 4 Defog, charge/Power Herb presentation and configuration consistency. Changed battle groups, Complete Edition features and flash saves pass 137 native tests. Ordinary play has reached Rustboro, including Norman/Wally, Scott and the first Team Aqua battle. Full story, Frontier, event travel/capture, portrait and hardware QA remain open. Checkmarks denote implemented alpha systems, not final-release QA. See [status and limitations](docs/COMPLETE_EDITION_STATUS.md) and [the field guide](docs/COMPLETE_EDITION_FIELD_GUIDE.md).
