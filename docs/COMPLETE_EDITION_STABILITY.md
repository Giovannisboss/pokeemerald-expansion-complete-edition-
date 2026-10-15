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
