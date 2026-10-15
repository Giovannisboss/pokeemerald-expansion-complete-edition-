# Complete Edition — Alpha 2.3

**Development milestone; final-release QA remains open.** No moves or abilities
have been removed. The physical/special split and Gen 4 defaults remain enabled.

## Implemented systems

- All 493 Gen 1–4 base species, universal shiny generation, no Fairy type.
- Natural multi-generation habitats across 105 wild tables; reusable TMs and local trade evolutions.
- Twelve catchable starter sites, 24 visiting leaders, the eight-round World Tournament and four postgame superbosses.
- Steven as Champion, with moderately raised main-story trainer levels.
- Nature, IV and EV services; 17 PC boxes with 510 slots and flash-save recovery.
- Shiny Rayquaza title artwork.
- Seventh-badge research catalogue and 29 new legendary world trails, including linked quests and capture-only completion flags.

The [field guide](COMPLETE_EDITION_FIELD_GUIDE.md) and
[legendary trails guide](COMPLETE_EDITION_LEGEND_TRAILS.md) describe locations and gates.
Implementation is distinct from ordinary-play verification.

## Alpha 2.3 corrections

- Defog clears hazards on its selected target's side under Gen 4 rules and preserves the other side. Ally targets in doubles receive the same treatment for hazards and screens.
- Gen 4 Defog lowers evasion through Substitute. Its minimum-evasion refusal remains intact; Gen 5 behavior is checked separately.
- Semi-invulnerable moves animate before their charge message under older move data. Power Herb now prints the subsequent attack message.
- Beat Up reads its own generation setting for typeless versus Dark damage; Future Sight retains its separate type setting.
- Conversion 2's target follows its own generation setting consistently with the effect implementation.
- Battle fixtures select Sturdy and Lightning Rod's modern behavior explicitly where required. Beat Up expectations use Gen 4's ten base power and a non-Fairy resistance fixture. Conversion 2's status-move case uses Confuse Ray without relying on later Curse typing.
- Partner switch-message fixtures follow the engine's battler order. No battle-order gameplay change was made.

## Verification

Ubuntu 24.04, ARM GCC 13.2.1, binutils 2.42 and mGBA 0.10.2.
The 938 production objects and 1,912 test objects pass ARM object-integrity checks.
All 84 added placements pass terrain, elevation, adjacency, overlap and event-limit validation.

Changed battle groups, Complete Edition features and actual flash saves pass
**137 tests**, with six TODOs and one assumption failure reported separately.
This includes 21 Defog cases, 13 Conversion 2 cases, all six parameters of each
semi-invulnerable charge/Power Herb scenario, 34 Complete Edition cases and four
flash-save cases. See `qa/2026-10-15-alpha-2-3-targeted.json`.

The final-source full audit completed **5,906 outcomes**: **5,276 PASS**, **119
failing outcomes** (104 FAIL, nine FLAKY, six INVALID), 65 assumption failures,
16 known failures, 421 TODOs and nine expected outcomes. No TIMEOUT or ERROR
occurred. This improves on Alpha 2.2's 139 failing outcomes but is not release-clean.
See `qa/2026-10-15-alpha-2-3-full.json` for every failure.

Ordinary-input testing has reached Rustboro City: the opening story, first
rival, Pokédex, running shoes, early trainer wins, a loss/whiteout recovery,
Petalburg/Norman dialogue, Wally's catching tutorial and Scott's introduction.
Cindy, James, Winston and Haley were defeated. Mudkip fainted against Haley;
Sentret finished the battle. Rustboro nurse healing restored Mudkip to 44/44
HP at level 12 and Sentret to 17/17 HP at level 4. An ordinary save and
fresh final-ROM process reloaded this Rustboro checkpoint. The ordinary Alpha 2.2 battery save loaded in
a fresh Alpha 2.3 emulator process at the woods entrance; the Bulbasaur site's
first-badge refusal was displayed. The first Team Aqua grunt was defeated, and
the Great Ball reward was confirmed in the Bag. Earlier QA covers BOX17, nature/EV purchases,
healing, a shiny Sentret capture, legendary hints and the pre-badge catalogue refusal.
This is not a complete Hoenn or Frontier playthrough.

## Build, patch and saves

- ROM SHA-256: `451840cb5dc1f0a1d11636f33002d4d8ab72964da57f2dac38dcfb01e75ad4f1`.
- Linked ROM: 16,557,400 bytes; padded ROM: 16 MiB; standard GBA ceiling: 32 MiB.
- EWRAM: 235,496/262,144 bytes; IWRAM: 28,364/32,768 bytes.
- Clean patch input: Emerald US/EU revision 0, SHA-1 `f3ae088181bf583e55daf962a92bb46f4f1d07b7`, CRC32 `1f1c08fb`.
- BPS creation verifies an exact round trip against the compiled target.
- Alpha 2 / 2.1 / 2.2 battery saves remain compatible. Back up saves before upgrading; load the normal battery save rather than an older emulator save state.
- Alpha 1/original saves are incompatible. No retail or compiled ROM is committed.

## Required before final release

- Complete the original story, all Gym gates, Champion/Hall of Fame and postgame unlocks using ordinary inputs.
- Exercise all seven Frontier facilities, a full tournament, visiting leaders and superbosses, including defeat/retry and facility saves.
- Travel to and capture/save/reload all starter and legendary world events.
- Finish storage/menu edge cases, full-party/full-PC gifts and service transactions during play.
- Resolve or explicitly classify the full-suite regressions, then pass the agreed release profile.
- Replace temporary Johto/Sinnoh leader and Gold/Silver portraits; polish event presentation and balance through playtesting.
- Test timing, audio and a flashcart on real GBA hardware. Hardware testing has not been completed.
