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

**Status:** Alpha 2.5 completes the full native audit with 5,397 passes and zero unexpected failures, down from 108 in Alpha 2.4. The 16 known failures, 421 TODOs and 63 assumption skips remain visible. Three actual flash-storage tests pass. Native story QA verifies shiny Marshtomp evolution, fixes the Rusturf reset caused by disabled visitor graphics, and completes Peeko rescue/Devon Parts recovery with a fresh save reload. Final outcome coverage adds a graphics regression and verifies all 5,907 expected outcomes across the broad recheck and focused completion; the incomplete recheck is labelled explicitly. Story/Frontier, world-event captures, portraits and hardware QA remain open. Checkmarks denote implemented alpha systems, not final-release QA. See [status and limitations](docs/COMPLETE_EDITION_STATUS.md).

**2026-10-16 progress:** Ordinary-play QA now reaches the Knuckle Badge: Devon,
PokeNav/Match Call, Rustboro rival, Briney's voyages, all six Dewford Gym trainers,
blackout/retry and Brawly victory are verified. EV reset, exact allocations and
the 510-total limit pass through the normal adviser UI. A fresh normal-save reload
retains two badges, level-22 Marshtomp and all progress. The unchanged Alpha 2.5
ROM rebuilds identically and 38 focused native checks pass. Next checkpoint:
Granite Cave/Steven's Letter and the Slateport boat unlock.
