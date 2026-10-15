# Stability work in progress

This is not a finished-release certification. The remaining story, event,
Frontier and hardware checks in COMPLETE_EDITION_STATUS.md still apply.

## Verified corrections

- Fixed an infinite stat-change loop: an empty stat queue now advances to the
  next battler. The old Gen 4 Charge data reached this case and timed out.
- Restored Charge's Gen 4 Special Defense increase, matching its description.
  Both an ordinary use and use at maximum Special Defense finish correctly.
- Made Charge's runtime generation override apply consistently to its timer
  and consumption logic. Gen 9 test fixtures explicitly select Gen 9 rules.
- Corrected Lightning Rod and Storm Drain descriptions to avoid promising the
  Gen 5 absorption/Sp. Atk effect under Gen 4 rules.
- Replaced Thunderbolt with Shock Wave in redirection-only tests, preventing
  secondary paralysis from interfering with the expected following move.
- Made held-item restoration obey runtime configuration in both restoration
  paths. A capture test now checks both Gen 4 and Gen 9 outcomes.
- Reworked Filter's fixture to exercise Gen 4 Mr. Mime without requiring Fairy.
- Added production-default battle regressions for physical Water attacks,
  special Ghost attacks, Technician and Charge. No move or ability was removed.

The complete focused run passed **147 tests, with 4 assumption skips and no
failures**, across all fifteen groups in tools/complete_edition/test.sh.
The seven new battle regressions are included in the 24 Complete Edition tests.
Sleep fixtures now apply their generation settings consistently; an additional
regression covers all four Gen 4 sleep durations. Forewarn's empty-field fixture
explicitly selects Gen 5 Healing Wish timing instead of assuming it under Gen 4.
Its equal-power fixtures now use moves that actually share their power in Gen 4.
This profile is deliberately scoped; it does not imply the upstream suite passes.

## Broad audit

The completed audit before the Charge corrections recorded 5,901 outcomes:
5,170 PASS; 213 failing outcomes (171 FAIL, 26 FLAKY, 7 TIMEOUT, 6 INVALID,
3 ERROR); 18 KNOWN_FAILING; 70 ASSUMPTION_FAIL; 421 TO_DO; and 9 expected
failures (including two intentional crash tests). The count improves on the
previous completed audit, but still blocks a finished-release claim.

A subsequent run with 5,811 outcomes was rejected as regression evidence: seven
empty test objects left after an interrupted streaming compile omitted tests.
All seven were removed and rebuilt. The Makefile now honours KEEP_TEMPS for
tests as well as production code; object guards validate ARM ELF headers, section
table bounds and expected source-object coverage. Production objects were intact.
A deliberately failing compiler is correctly rejected with exit status 2.
The integrity-checked full run completed with **5,891 outcomes: 5,189 PASS;
185 failing outcomes (170 FAIL, 6 FLAKY, 6 INVALID, 3 ERROR); no TIMEOUT;
69 ASSUMPTION_FAIL; 18 KNOWN_FAILING; 421 TO_DO; and 9 expected outcomes**.
All 1,910 ARM objects were validated, including all 973 test source objects.
This snapshot preceded the two Forewarn equal-power fixture corrections and
the starter-preview palette change. The broad suite still exits with failure.

The check script now continues through all focused groups after a failure,
retains its failing exit status, streams output, and writes machine-readable
summaries. The summarizer checks the final reported total before marking a run
complete. Assumptions, TODOs, known failures and deliberate crash outcomes are
retained explicitly.

## Normal-input playthrough

The headless controller uses native button inputs and exposes no memory-write
command. The opening title/menu, truck exit, house scenes, clock setup, rival
introduction, Birch rescue sequence and starter-selection UI were exercised.
Mudkip was selected, Birch's rescue battle was won, and the lab dialogue completed.
An ordinary in-game save was written and loaded in a fresh emulator process with
the rebuilt ROM, without loading a checkpoint. Location, party, shiny palette,
level, HP, nature and moves survived. mGBA stores 128 KiB of flash plus its RTC
trailer. A normal Route 101 grass encounter produced a visibly shiny Pidgey
before the first badge, confirming natural Kanto availability in play.
This is opening QA, not a completed story or Frontier playthrough.

Normal play also exercised Centre healing and the paid Modest battle-nature
service, and displayed BOX17 by scrolling left from BOX1 in the ordinary PC UI.
The opening starter confirmation used a normal palette despite the actual shiny
starter; it now follows the universal-shiny configuration. A fresh new game
visually confirmed the shiny Torchic preview in the rebuilt production ROM.

The optional controller supports image captures, emulator checkpoints,
read-only position inspection and a command journal. Emulator checkpoints are
private test aids; the native battery-save check above used a fresh process.
The controller now attaches the ordinary battery-save file, can advance dialogue
until field controls unlock, and stops walking when a wild battle begins.

## Additional regression triage

Encore's modern duration fixtures now explicitly select modern target/input
rules. Its sleep fixture fixes the sleep RNG because sleep length is not what
that case tests. The Champions priority fixture enables dynamic turn order.
All 18 Encore cases pass. Dancer's four forced-move interaction cases also pass.
Mental Herb and Illuminate now honour runtime configuration consistently in
battle/AI checks; production Gen 4 defaults are unchanged. Mental Herb (8),
Anger Point (4) and Keen Eye (6) groups pass. New production regressions confirm
that Gen 4 Mental Herb does not cure Torment/Taunt/Heal Block and that Illuminate
does not block Sand Attack. The Complete Edition group passes 26 tests before
adding the new legendary-trail tests. These targeted counts are not a replacement
for a completed new broad run.

## Legendary trails under verification

Twenty-nine distinct world encounters supplement the six original Hoenn legend
events. Their hints, locations, capture-only completion and quest prerequisites
are authored in data/complete_edition_world.json. See the legendary trails guide.
Generation is timestamp-idempotent. Static checks cover 84 added object placements,
unique encounters, cancel-safe hints and an acyclic prerequisite graph. The new
native gates/encounter factories and ordinary event interactions are being checked;
this is not completed event/playthrough QA.

The ordinary new-game run defeated the first rival on Route 103 and completed
her following dialogue. This remains an early-game playthrough.

## Continued development — Alpha 2.2

The first complete audit of this continued work recorded **5,897 outcomes**:
5,212 PASS; 170 failing outcomes (158 FAIL, 6 FLAKY, 6 INVALID);
67 ASSUMPTION_FAIL, 18 KNOWN_FAILING, 421 TO_DO and 9 expected outcomes.
There were no TIMEOUT or ERROR outcomes. The complete machine-readable backlog
is in `qa/2026-10-15-before-final-fixture-fixes.json`. This snapshot precedes
the Growth correction and the final targeted fixture corrections.

A real production defect was found in Growth: sunlight incorrectly doubled
its stat boost under Gen 4. Both battle execution and AI now restrict that
bonus to Gen 5+. Gen 4 Growth raises Special Attack by one, with or without sun.
Its Attack data now follows the same generation switch as its description.

Generation-aware test accessors now handle Growth, Sheer Cold and Transform
consistently in the Gen 4 build. Modern Embargo reflection tests explicitly
select modern flags; a separate production-default regression verifies that
Gen 4 Magic Coat does not reflect Embargo. The Mega Transform fixture selects
Gen 5+ form-change rules, while a separate Gen 4 battle verifies Ditto identity
after fainting. Universal-shiny expectations also apply to Transform.

The experience fixture now verifies both Gen 4 trainer bonus/shared awards and
modern full awards. Future Sight comparisons use an equally powerful non-Psychic
move so that STAB, Twisted Spoon and Psychic Gem do not contaminate the baseline.
Color Change explicitly checks typeless Gen 4 and typed Gen 5 delayed attacks.
Healing Wish trainer-slide cases select their required end-of-turn replacement
rules. All 75 trainer-slide cases pass; Future Sight (21), experience (9),
stat-change leak checks (2), Sheer Cold/OHKO (16), Embargo (17) and Transform (13)
pass in focused reruns. Upstream TODO and KNOWN_FAILING cases remain recorded.
The Complete Edition group passes **34 tests**. No move or ability was removed.

Normal-input QA now includes Pokédex handover, running shoes, a shiny Sentret
caught on Route 101 and added to the party/Dex, healing both party members,
and victories over Calvin and Rick on Route 102. A fresh production emulator
process loaded the ordinary battery save with the Pokédex progress intact.
The legendary hints menu and pre-Mind-Badge catalogue refusal were checked
in the production ROM. The tester selected Fast text through the ordinary
Options menu. This is still early-game QA, not a full story playthrough.

The artwork service rejected the requested Gold sprite; no replacement trainer
portrait is claimed. Remaining portraits, full story/Frontier/event interaction
QA and unresolved broad failures continue to block a final release.

## Final Alpha 2.2 audit snapshot

The final native rerun completed **5,905 outcomes**: **5,253 PASS; 139 failing
outcomes (123 FAIL, 10 FLAKY, 6 INVALID); no TIMEOUT or ERROR**. It also recorded
65 ASSUMPTION_FAIL, 18 KNOWN_FAILING, 421 TO_DO and 9 expected outcomes.
See `qa/2026-10-15-alpha-2-2-full.json` for every unresolved case.
This improves on the prior 185-outcome snapshot but does not pass the full suite.
The 10 flaky outcomes include repeated outcomes from unstable tests, not ten
confirmed independent gameplay defects. Every unresolved result remains visible.

Native totals agree with all 5,905 recorded outcomes and ARM-object integrity
passes. Editing the long-running shell wrapper during execution caused a
trailing parse error after these totals were saved; the current wrapper passes
`bash -n`. This trailing wrapper error is separate from the native failures.

The expanded focused profile completed **37 groups, with 403 PASS, 4 assumption
skips, 2 upstream KNOWN_FAILING and 11 TODO outcomes; no unexpected failures**.
This is a scoped gate, not a replacement for the 139-failure broad backlog.
Its group-by-group report is `qa/2026-10-15-alpha-2-2-focused.json`.

The ordinary-input run also defeated Allen, then lost to Tiana with both
party Pokémon fainted. The normal whiteout sequence returned the player to
Oldale and Nurse Joy restored both Pokémon. This exercises the loss/recovery
path; it is not a Tiana victory or further story progress.

The unchanged current shell wrapper was then executed normally and completed
all 37 focused groups with exit status 0, reproducing the 403-pass profile.
The final Alpha 2.2 production ROM was loaded in a fresh mGBA process using the
ordinary battery save after whiteout/recovery. Mudkip (level 9, 36/36 HP) and
the caught Sentret (level 3, 15/15 HP) were both present and healed.


## Alpha 2.3 continued stabilization (2026-10-15)

The targeted profile passes 137 cases with six TODOs and one assumption failure
recorded separately. It includes all 21 Defog cases, all 13 Conversion 2 cases,
all six parameters of both semi-invulnerable charge scenarios, partner switch
messages, Beat Up, Focus Punch, Stockpile, paralysis, Complete Edition gates
and actual flash saves. Two former known Defog failures are now ordinary passes.

Defog clears the selected side in Gen 4 (including ally targets), respects the
generation-specific Substitute behavior and retains minimum-evasion refusal.
Power Herb prints the subsequent attack string for older semi-invulnerable moves.
Beat Up's type and Conversion 2's target read their dedicated generation settings.
No moves or abilities were removed, and no battle-order gameplay change was made.

The first continued broad run completed 5,906 outcomes: 5,272 PASS, 123 failing
outcomes (108 FAIL, nine FLAKY, six INVALID), 65 assumption failures, 16 known
failures, 421 TODOs and nine expected outcomes. It had no TIMEOUT or ERROR and
precedes the final message/fixture corrections. Its report is retained as
`qa/2026-10-15-alpha-2-3-before-message-fixes-full.json`.

The final-source broad audit completed all 5,906 outcomes: 5,276 PASS, 119
failing outcomes (104 FAIL, nine FLAKY, six INVALID), 65 assumption failures,
16 known failures, 421 TODOs and nine expected outcomes. No TIMEOUT or ERROR
occurred. The normal Make failure status reflects the remaining failed cases;
there was no wrapper parse error. The final report is
`qa/2026-10-15-alpha-2-3-full.json`. Alpha 2.2 had 139 failing outcomes.
Unresolved outcomes remain explicit; none were reclassified as passes.

The final production build uses SHA-256
`451840cb5dc1f0a1d11636f33002d4d8ab72964da57f2dac38dcfb01e75ad4f1`.
BPS generation verified an exact source-to-target round trip. ROM usage is
16,557,400 bytes; EWRAM remains 235,496 bytes and IWRAM 28,364 bytes. All 938
production and 1,912 native-test objects pass the integrity guard.

Ordinary buttons advanced the previous save through Petalburg/Norman, Wally's
catching tutorial, Scott, Cindy, the woods and the first Team Aqua grunt. The
Great Ball reward was confirmed in the Bag. A fresh emulator process loaded the
ordinary battery save on the final ROM. The Bulbasaur site refused access before
the first badge. No story flags, levels, items or party data were injected.
The host QA controller's `fight` command reads battle UI state and presses normal
buttons; it is not part of the game. It requires a usable selected move and does
not handle all party/Bag/learning states. It was exercised in wild and trainer
battles with a bounded frame budget.

The final ROM subsequently passed James, Winston and Haley and reached Rustboro.
Mudkip fainted against Haley and Sentret completed the fight. Rustboro nurse
healing restored both Pokemon; a normal save and fresh final-ROM process loaded
the Rustboro Centre checkpoint at (7,4). This remains early-game QA.
Full story, Frontier, all event travel/captures,
portraits and real hardware testing remain release blockers.
