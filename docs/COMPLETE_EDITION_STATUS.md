# Complete Edition — Alpha 2.4

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

## Alpha 2.4 corrections

- Roxanne and the Route 104 Bullet Seed gift now explain that TMs are reusable.
- Removed obsolete badge stat-boost claims from Roxanne, Norman and Tate/Liza. Gen 4 disables these boosts; HM permissions remain unchanged.
- All rampage paths consistently read the selected generation setting. Gen 4 behavior is retained; Gen 5 cancellation/confusion cases now select the same rules across move resolution, cancellation and end turn.
- Magic Coat tests distinguish Gen 4 hazards from Gen 5 reflection. Assurance fixtures explicitly select modern Infiltrator/Disguise behavior, and use a neutral target for the rounding comparison.
- The multi-hit Destiny Bond test actually uses both HP parameters and deterministic Gen 4 Bullet Seed damage. The paralysis AI fixture requests Gen 6 Electric immunity explicitly.
- The host QA controller now stops when another callback takes control; it does not press through party menus. A conservative walking planner was added. Neither tool is part of the game.

No move or ability was removed. These configuration fixes do not change the production Gen 4 defaults.

## Verification

Ubuntu 24.04, ARM GCC 13.2.1, binutils 2.42 and mGBA 0.10.2.
The 938 production objects and 1,912 test objects pass ARM object-integrity checks.
All 84 added placements pass terrain, elevation, adjacency, overlap and event-limit validation.

The targeted profile passes **106 tests**, including both generation variants
for rampage cancellation and Magic Coat, all Assurance/multi-hit/bad-move AI
cases, 34 Complete Edition cases and four actual flash-save cases. There are no
failed, TODO or assumption outcomes in this profile.
See `qa/2026-10-15-alpha-2-4-targeted.json`.

The complete battle-engine audit records **5,908 outcomes**: **5,289 PASS**,
**108 failing outcomes** (93 FAIL, nine FLAKY, six INVALID), 65 assumption
failures, 16 known failures, 421 TODOs and nine expected outcomes. No TIMEOUT or
ERROR occurred. Alpha 2.3 had 119 failing outcomes. Remaining failures are
explicit in `qa/2026-10-15-alpha-2-4-full.json`; this is not release-clean.
Map-dialogue edits made after the audit began do not change the battle engine;
production play verifies the reusable-TM explanation separately. All 11 changed
dialogue lines pass the normal-font width check (maximum 199/208 pixels).

Ordinary buttons advanced the Alpha 2.3 battery save through Josh, Tommy and
Marc, then defeated Roxanne on the Alpha 2.4 build. The Stone Badge and TM39
were awarded. Roxanne's reusable-TM message displays correctly, Mudkip learned
Rock Tomb over Growl, and TM39 remained in the Bag. A normal save and fresh
process reloaded the one-badge checkpoint. The Aqua chase and Devon recovery request completed, and
the release ROM reloaded that save at Rustboro (29,10). All earlier opening/PC/services,
catching and legendary-hint checks remain documented in the stability report.

Evolution is not yet verified in ordinary play. An isolated callback-guard test
stopped at the mandatory party screen after a faint; it did not complete an
evolution test. Gold portrait generation was rejected and produced no artwork.

## Build, patch and saves

- ROM SHA-256: `7210f3eb6c61b01d286ea96bf12b017c3cfe41022a15579cf1234c00141b11b3`.
- Linked ROM: 16,557,360 bytes; padded ROM: 16 MiB; standard GBA ceiling: 32 MiB.
- EWRAM: 235,496/262,144 bytes; IWRAM: 28,364/32,768 bytes.
- Clean patch input: Emerald US/EU revision 0, SHA-1 `f3ae088181bf583e55daf962a92bb46f4f1d07b7`, CRC32 `1f1c08fb`.
- BPS creation verifies an exact round trip against the compiled target.
- Alpha 2 / 2.1 / 2.2 / 2.3 battery saves remain compatible. Back up saves before upgrading; load the normal battery save rather than an older emulator save state.
- Alpha 1/original saves are incompatible. No retail or compiled ROM is committed.

## Required before final release

- Complete the original story, all Gym gates, Champion/Hall of Fame and postgame unlocks using ordinary inputs.
- Exercise all seven Frontier facilities, a full tournament, visiting leaders and superbosses, including defeat/retry and facility saves.
- Travel to and capture/save/reload all starter and legendary world events.
- Finish storage/menu edge cases, full-party/full-PC gifts and service transactions during play.
- Resolve or explicitly classify the full-suite regressions, then pass the agreed release profile.
- Replace temporary Johto/Sinnoh leader and Gold/Silver portraits; polish event presentation and balance through playtesting.
- Test timing, audio and a flashcart on real GBA hardware. Hardware testing has not been completed.
