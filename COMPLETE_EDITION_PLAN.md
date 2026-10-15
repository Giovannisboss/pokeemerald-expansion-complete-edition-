# Pokémon Emerald: Complete Edition

Fan-made ROM hack built on RHH pokeemerald-expansion.

## Design target
- Original Hoenn adventure and Battle Frontier retained where practical.
- National Pokédex species #1–493 obtainable in one save, without trading.
- Every Pokémon shiny, including wild, gift, egg, static and trainer Pokémon.
- Generation 4 physical/special move split and Gen 1–4 mechanics; no Fairy type.
- Steven replaces Wallace as Champion; moderate main-story difficulty.
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

**Status:** Alpha 1 implements the listed systems and compiles. Focused emulator checks pass; full-suite regression failures and end-to-end playthroughs remain open. Checkmarks mean the alpha implementation exists, not that final-release QA is complete. Codespaces configuration is supplied; the equivalent Ubuntu build was tested locally. Availability currently uses a postgame research encounter catalogue. Some portraits are temporary. See [the current status and limitations](docs/COMPLETE_EDITION_STATUS.md).
