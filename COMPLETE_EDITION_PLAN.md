# Pokémon Emerald: Complete Edition

Fan-made ROM hack built on RHH pokeemerald-expansion.

## Design target
- Original Hoenn adventure and Battle Frontier retained where practical.
- National Pokédex species #1–493 obtainable in one save, without trading.
- Every Pokémon shiny, including wild, gift, egg, static and trainer Pokémon.
- Generation 4 physical/special move split and Gen 1–4 mechanics; no Fairy type.
- Dynamax and Gigantamax disabled for players and trainers; shared save structures retained.
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

**Status:** Alpha 2.5.1 disables Dynamax/Gigantamax and completes a fresh full native audit: 5,400 passes, zero unexpected failures and 5,909 recorded outcomes. The 16 known failures, 421 TODOs and 63 assumption skips remain visible. The rebuilt production ROM matches the existing Alpha 2.5.1 checksum exactly. Checkmarks denote implemented alpha systems, not final-release QA. Story/Frontier, world-event captures, portraits and hardware QA remain open. See [status and limitations](docs/COMPLETE_EDITION_STATUS.md).

**2026-10-16 progress:** Ordinary-play QA has completed the Knuckle Badge, Granite Cave/Steven's Letter and Slateport's museum/Aqua storyline. The latest recorded normal save is Slateport Centre with two badges, Marshtomp level 24 and Cleffa level 10. The Route 110 rival is reached but unbeaten. This continuation completed the fresh full native audit and strengthened result checking; it did not advance the ordinary playthrough. Next story task: defeat the Route 110 rival and continue to Mauville.
