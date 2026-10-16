# Complete Edition — Alpha 2.5.1

**Development milestone; final-release QA remains open.** No moves or abilities
have been removed. The physical/special split and Gen 4 defaults remain enabled.

## 2026-10-16: complete Alpha 2.5.1 native audit

A fresh clean GitHub runner built the no-Dynamax source and completed the entire
native suite at commit `a583fe1aea3671bae1ff280abe856b323ca3832f`.
The run records **5,400 PASS and zero unexpected failures across 5,909 outcomes**.
It retains **16 KNOWN_FAILING, 421 TO_DO, 63 ASSUMPTION_FAIL, seven EXPECTED_FAIL
and two deliberate expected-crash outcomes**. The native TOTAL footer, process
exit status, result checker and final workflow all pass. This completed run
replaces the need to rely on the historical combined partial-run coverage for
the current battle/test tree; those older reports remain historical evidence.

The log checker now rejects unexpected or ambiguous crashes, unrecognized result
statuses, unexpected passes and failing summary footers. It preserves the native
runner's explicitly green expected-crash outcomes. Four host regression tests
cover 19 scenarios and pass locally and in CI. Existing known-failure and TODO
markers were not increased or removed to obtain a passing result.

The production ROM checksum remains
`c4b86f0dca54f7118252b5209081df5b282af8c84ad06d4b8081291775313948`;
these host verification changes do not modify gameplay or saves. All 938
production and 1,914 test object headers validate, together with the map,
graphics, starter, legendary and seventh-badge gates.
See [full-audit evidence](qa/2026-10-16-alpha-2-5-1-full.json) and the
[completed workflow](https://github.com/Giovannisboss/pokeemerald-expansion-complete-edition-/actions/runs/38932717701).

No ordinary-play progress is claimed for this pass. The recorded story position
remains Slateport with two badges, before defeating the Route 110 rival. The
prior live emulator session is not available in this continuation environment.
Original-story/postgame/event playthrough, portraits and real-hardware QA remain
required before a final release.

## Alpha 2.5.1: Dynamax removed from gameplay

Dynamax and Gigantamax are globally disabled for both players and trainers.
The production eligibility function compiles to `return FALSE`, and direct
activation compiles to a no-op. The normal battle UI cannot offer the feature.
Shared IDs, save data and HP cleanup helpers are retained to protect compatibility.
Gen 4 defaults and the physical/special split remain unchanged.

The final isolated build passes **40 focused native Complete Edition tests**,
including both-side and direct-activation rejection, maximum Dynamax-level and
Gigantamax metadata, and flash storage regressions. All 938 production object
headers and the map/resource validation pass. A fresh process loads the prior
Alpha 2.5 two-badge save and verifies normal field movement at Dewford Gym.
ROM SHA-256: `c4b86f0dca54f7118252b5209081df5b282af8c84ad06d4b8081291775313948`.

Other pending battle repairs were excluded after broad testing found regressions;
this patch contains only the Dynamax policy and its tests. The historical full
audit below still describes Alpha 2.5: its 16 known failures are not claimed as
resolved in this release. Two of those concern unused upstream Dynamax AI.
Original-story/postgame, portrait and hardware release QA remains open.
See `qa/2026-10-16-alpha-2-5-1-no-dynamax.json`.

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

## 2026-10-16: Dewford progression verified

The production ROM remains Alpha 2.5 with the same SHA-256 below. A clean rebuild
matches it byte for byte; all 938 production object headers validate. The focused
Complete Edition native suite completes with **38 PASS and zero failures**.
The earlier full audit has not been rerun or replaced by this focused check.

Ordinary buttons now verify the Devon handoff, Great Ball, Letter/PokeNav award,
Match Call tutorial and Mr Stone call, Rustboro rival victory, return through
Petalburg Woods, and both directions of Mr Briney's Dewford voyage. Dewford
Centre healing and a fresh battery reload work. All six Gym trainers are defeated,
their lighting changes work, and Brawly's initial defeat/blackout and Centre
recovery are followed by a successful retry. His badge, Bulk Up TM, Match Call
registration and fully lit Gym sequence complete.

The training adviser is exercised through the normal UI: EV reset, 252 HP and
252 Special Attack, rejection of a total of 511, and acceptance of exactly 510
with six Speed EVs. A normal two-badge save then reloads into the Gym in a fresh
process. Read-only battery validation checks every sector in both slots and
confirms all six trainer flags, Brawly, both badges and the exact EV allocation.
No party data, flags, items, levels or memory were injected; no save states were used.

The current durable checkpoint is **Dewford Gym (4,4), two badges, shiny Marshtomp
level 22**, with Sentret still in BOX1. Next: obtain Flash in Granite Cave, deliver
the Letter to Steven, and verify the Slateport boat unlock. See
`qa/2026-10-16-alpha-2-5-dewford.json` for scope and evidence. The QA controller's
optional field-lock argument now stops walking input during field scripts;
legacy walking commands remain supported. This host-tool change does not change
the game binary.

## 2026-10-16: Granite Cave and Slateport progression verified

Normal play now covers the Flash award, Cleffa capture and HM teaching, Flash
illumination, Steven's Letter/Steel Wing/registration/departure, and the unlocked
Slateport voyage. Steven's departure survives a fresh battery reload. Dock's
shipyard dialogue, museum ticket, both Aqua fights, Archie, Devon Parts delivery,
and Scott/Birch registration sequences complete. Route 110 opens normally.

A normal Slateport Centre save reloads in a fresh process with field movement;
both slots pass every sector checksum. This checkpoint has two badges, Marshtomp
level 24 and Cleffa level 10. The rival was reached but not defeated; subsequent
ordinary losses reflect poor controller strategy and party coverage. There is
no new production game fix or new full-suite result in this pass. Host-only
routing and battle controls are being improved to reduce routine input overhead.
See `qa/2026-10-16-alpha-2-5-slateport.json`. The Dewford checkpoint above remains
a historical milestone, not the latest progression position.

## Alpha 2.5 historical build, patch and saves

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
