# Complete Edition — Alpha 2.5

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

## Alpha 2.5 corrections and audit

The complete frozen-engine native audit now records **5,397 PASS and zero
unexpected failure outcomes** across **5,906 outcomes**. Alpha 2.4 recorded
108 unexpected failures. The new run has no FAIL, FLAKY, INVALID, TIMEOUT or
ERROR results. There are still **63 assumption skips, 16 known failures,
421 TODOs and nine expected outcomes**. Known-failing/TODO counts were not
increased to obtain this result. These are runner outcome counts; parameterized
families and flaky retries can change the number of emitted rows.
See `qa/2026-10-15-alpha-2-5-full.json` and the comparison report.
That completed battle audit preceded the field-resource correction below. Final
named-outcome coverage verifies 5,398 passes across 5,907 outcomes: the later
broad recheck lacked a completion footer and three results, so those three were
verified in a complete Strong Winds rerun. The incomplete log is not presented
as a completed audit; details are in `qa/2026-10-15-alpha-2-5-final-coverage.json`.

Many failures were tests assuming newer rules despite this project's Gen4
profile. Fixtures now select the required generation explicitly. Runtime test
accessors honor those selections for relevant move/ability data; production
Gen4 defaults and the physical/special split remain intact. No move or ability
was removed. Damage-ratio fixtures use Strength's stable 80 power to avoid
Tackle's Gen4 base-power rounding ambiguity.

Conversion 2 now checks missing/unavailable move history before looking up its
effect, preventing an invalid lookup after a failed move. AI evaluates usable
observed history rather than treating it like Splash. Dedicated tests cover
Gen4/Gen5 decisions and safe failure after Protect. Paired behavioral tests also
cover sound/Substitute rules, ability-weather duration and Zen Mode Skill Swap.
Targeted reruns record **331 PASS**, with 11 existing TODOs, three known failures
and three assumption skips; the final full audit covers the complete final engine.
All three actual flash-storage tests pass in a separate sequential rerun.

## Visiting NPC field-restoration fix

Native play reproduced a post-battle reset in Rusturf Tunnel. A read-only CPU
trace identified a null graphics resource for the placed Brock visitor during
field-sprite restoration. Nine placed NPC graphics were still inside FireRed/
LeafGreen-only asset guards. Their existing images, frame tables, graphics info
and pointer entries are now enabled in Emerald too. A native regression checks
all 61 distinct CE_ placement graphics IDs, and map validation keeps that list
in sync. No NPC, move or ability was removed to avoid the crash.

## Ordinary-play scope

The opening, first rival, catching, PC/services, Stone Badge, TM39 teaching/reuse,
and one-badge save reload remain verified from earlier milestones. This pass
observed Mudkip evolve into shiny Marshtomp and return to field movement on
both Alpha 2.4 and the Alpha 2.5 release ROM.
Route 116 wild/trainer battles, normal blackouts and nurse recovery were exercised.
The host controller now optionally confirms default enemy targets in doubles;
important move/target choices still need manual review. The controller is QA-only.

The post-battle reset reproduced on Alpha 2.4 and the initial Alpha 2.5 build;
the graphics fix above addresses its traced cause. The final ROM replay returns
safely from both wild and grunt battles and completes the Devon Parts award and
Mr Briney/Peeko reunion/exit sequence. A fresh Alpha 2.5 process loaded a normal saved Centre checkpoint after
Sentret was deposited in BOX1. The final normal save reloads in a fresh process at Rusturf Tunnel (13,5), with
Devon Parts still in the Key Items pocket. Marshtomp is level 17; Sentret is in
BOX1. The next story task is returning the package to Devon in Rustboro.

## Build, patch and saves

- ROM SHA-256: `8edbd04b52db94e4c4ad52ec161832d0b0033193e96d6f9072d677c10d76a1f6`.
- Linked ROM: 16,568,604 bytes; padded ROM: 16 MiB; standard GBA ceiling: 32 MiB.
- EWRAM: 235,496/262,144 bytes; IWRAM: 28,364/32,768 bytes.
- Clean patch input: Emerald US/EU revision 0, SHA-1 `f3ae088181bf583e55daf962a92bb46f4f1d07b7`, CRC32 `1f1c08fb`.
- BPS creation verifies an exact round trip against the compiled target.
- Alpha 2 / 2.1 / 2.2 / 2.3 / 2.4 battery saves remain compatible. Back up saves before upgrading; load the normal battery save rather than an older emulator save state.
- Alpha 1/original saves are incompatible. No retail or compiled ROM is committed.

## Required before final release

- Complete the original story, all Gym gates, Champion/Hall of Fame and postgame unlocks using ordinary inputs.
- Exercise all seven Frontier facilities, a full tournament, visiting leaders and superbosses, including defeat/retry and facility saves.
- Travel to and capture/save/reload all starter and legendary world events.
- Finish storage/menu edge cases, full-party/full-PC gifts and service transactions during play.
- Address known failures and assumption/TODO coverage, and maintain the zero-unexpected-failure audit.
- Replace temporary Johto/Sinnoh leader and Gold/Silver portraits; polish event presentation and balance through playtesting.
- Test timing, audio and a flashcart on real GBA hardware. Hardware testing has not been completed.
