# Complete Edition — Alpha 2.5.1

**Development milestone; final-release QA remains open.** No moves or abilities
have been removed. The physical/special split and Gen 4 defaults remain enabled.

## 2026-10-17: 18 portraits integrated; final native run active

All 18 dedicated portraits are integrated at `d801d69748baa9570049a23864c1be74ea00e37c`: 16 Johto/Sinnoh leaders, Gold and Silver. All 34 relevant trainer assignments use these assets. Local and CI checks pass for distinct indexed 64x64 artwork, transparent index zero, at most 16 palette entries, graphics mappings and preservation of all 158 existing portrait IDs. The save format is unchanged.

Production compilation and exact clean-reference/BPS round-trip verification pass. Portrait-enabled production SHA-256: `a7b4c7afba7792984779478a621df19bfb5ddb467d1733f8233f1257ca4509d7`. The owner's local clean ROM matches required SHA-1 `f3ae088181bf583e55daf962a92bb46f4f1d07b7`. CI rebuilds the matching reference from pinned pret sources and uploads no ROMs.

The new resource test initially triggered GCC's table-index bounds warning; `e082485208c5a3d1c3b21989ce480e103b33b2262` adds an explicit bounds guard without weakening assertions. [Final verification run 39059775787](https://github.com/Giovannisboss/pokeemerald-expansion-complete-edition-/actions/runs/39059775787), job117475162147, is active at this checkpoint. Do not claim its focused/full native results or downloadable patch until it completes. Earlier native totals below are historical baselines.

The owner will perform ordinary story/postgame and battle presentation verification. Those checks and hardware verification remain open. No ordinary gameplay progress is claimed here.

## 2026-10-17: earlier HP and full native verification

Source `a18692567ed17b4a1cef13fec1cf253167c72ae9` passed [run39030540953](https://github.com/Giovannisboss/pokeemerald-expansion-complete-edition-/actions/runs/39030540953), job117389924632. Focused Complete Edition: **51/51 PASS**. Full suite: **5,424 PASS / 5,922 outcomes / zero unexpected failures**. Strict local reclassification of the full-suite section confirms all5,922 rows, two deliberate green crashes and zero failing footers. The same five known failures,63 assumption skips,421 TODOs and seven expected failures remain visible. The new HP family covers24 combinations and passes in both focused and full runs.

Production SHA256 is unchanged: `ab7793e8a2f73e56863c88daaf3d726b6ae515a78b8f67aed1f902651f14b040`. No production-game source changed. [Evidence](qa/2026-10-17-training-hp.json) records the exact tested source.

Patch-only packaging is now implemented at`c2ba95e743ede71005e5f31ad817bed9430dda0b`. [Release-tool CI39032789005](https://github.com/Giovannisboss/pokeemerald-expansion-complete-edition-/actions/runs/39032789005),job117396480178,passes all12 BPS/packaging methods. It requires the exact clean input,verifies an exact round trip,and produces onlyBPS,README,manifest and checksums. It rejects existing outputs and cleans staging after write failure. The unexecuted full-ROM uploader from1328b4d was removed at296a680;the current workflow does not publish full ROMs. No production patch has been generated in this pass because the matching input/target pair is not available locally. Packaging-only changes receive dedicated host CI;the passed native engine baseline above remains unchanged.

This remains a development build. Ordinary story/postgame verification is deferred,18 dedicated portraits remain unfinished, and final patch/release and hardware checks remain open.

## 2026-10-17: earlier training-boundary audit

Full run [39028497564](https://github.com/Giovannisboss/pokeemerald-expansion-complete-edition-/actions/runs/39028497564), job117384104598, source2973b74d8e405ad082714cb35c85f85ec453945c completed successfully. Production compilation, placement/gate validation, six BPS integrity tests, log-parser regressions and the full native suite passed. Strict local reclassification confirms **5,423 PASS / 5,921 outcomes / zero unexpected failures**, including all50 Complete Edition outcomes. Five known failures,63 assumption skips,421 upstream TODOs,seven expected failures and two deliberate expected crashes remain visible. No failure marker was removed or weakened.

The new coverage verifies exact510EV replacement/reduction, invalid IV-index rejection without cap consumption, Egg training rejection, and invalid script slots/operations. [Machine-readable evidence](qa/2026-10-17-training-boundaries.json) identifies the exact source and workflow.

Production SHA256 remains `ab7793e8a2f73e56863c88daaf3d726b6ae515a78b8f67aed1f902651f14b040`. Follow-up commit `a18692567ed17b4a1cef13fec1cf253167c72ae9` adds24 HP-training combinations and a focused Complete Edition step before the full audit; its CI is pending and is not part of the passed totals above.

Latest durable ordinary milestone is Granite Cave HM05, save SHA256`1295405399a5b6c9fa14fe236a09d0666b4400f06bb7285d999c44ad1360aae8`. The subsequent working save was not recovered in this environment. The owner deferred ordinary mGBA playthrough; do not treat that deferral as a pass or return to an older incompatible ROM. Steven Letter, story/postgame certification,18 dedicated portraits and final release sign-off remain open.

## 2026-10-16: reconciled pending fixes fully tested

Commit `adb01b50634e49c0d3dfbbd59d6d787dd549424b` passes all 21 affected native families and a fresh complete full suite: **5,418 PASS, zero unexpected failures, 5,916 total outcomes**. Five known failures, 63 assumption skips, 421 upstream TODOs and nine expected self-test outcomes (including two deliberate crashes) remain visible. The native footer, strict result checker, process exit and workflow all pass. See [machine-readable evidence](qa/2026-10-16-reconciled-fixes-full.json) and [completed workflow](https://github.com/Giovannisboss/pokeemerald-expansion-complete-edition-/actions/runs/38942000064).

The handoff patch was reconciled against the latest development source. Embargo's fixture now resolves its battler position correctly. Beat Up/Justified logic respects Gen4's typeless damage and uses cautious preliminary partner prediction. No global spread-move target reordering was introduced. Gen4 Roost rounding passes; its explicit modern-generation limitation remains visible. The tournament preserves an earned Gold Bottle Cap when the bag is full and allows exactly one collection after space is available. All five reward tests pass.

Production ROM SHA-256: `ab7793e8a2f73e56863c88daaf3d726b6ae515a78b8f67aed1f902651f14b040`. All 938 production and 1,915 test object headers validate. Dynamax/Gigantamax remain disabled. The five known failures cover two disabled Dynamax AI cases, two Gen8 Neutralizing Gas cases and Gen5+ Roost rounding; the Gen4 profile has dedicated passing coverage.

**Recovered-save correction:** the later Slateport playthrough remains documented, but its actual battery save was not recovered. The latest recovered save is Dewford after Brawly, two badges, shiny level-22 Marshtomp and Sentret in Box1. Resume Granite Cave, Flash and Steven's Letter unless a newer save is verified. This continuation has not advanced that save. Story/postgame verification, portraits and hardware QA remain open; the project is not a finished release.

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
