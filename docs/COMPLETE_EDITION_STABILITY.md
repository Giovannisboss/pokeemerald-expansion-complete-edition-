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

The complete focused run passed **136 tests, with 4 assumption skips and no
failures**, across all twelve groups in tools/complete_edition/test.sh.
The six new battle regressions are included in the 23 Complete Edition tests.
This profile is deliberately scoped; it does not imply the upstream suite passes.

## Broad audit

The completed audit before the Charge corrections recorded 5,901 outcomes:
5,170 PASS; 213 failing outcomes (171 FAIL, 26 FLAKY, 7 TIMEOUT, 6 INVALID,
3 ERROR); 18 KNOWN_FAILING; 70 ASSUMPTION_FAIL; 421 TO_DO; and 9 expected
failures (including two intentional crash tests). The count improves on the
previous completed audit, but still blocks a finished-release claim.

A subsequent full run is in progress. Do not subtract focused fixes from that
old total and present the arithmetic as a completed new full run.

The check script now continues through all focused groups after a failure,
retains its failing exit status, streams output, and writes machine-readable
summaries. The summarizer checks the final reported total before marking a run
complete. Assumptions, TODOs, known failures and deliberate crash outcomes are
retained explicitly.

## Normal-input playthrough

The headless controller uses native button inputs and exposes no memory-write
command. The opening title/menu, truck exit, house scenes, clock setup, rival
introduction, Birch rescue sequence and starter-selection UI were exercised.
Mudkip was selected and the first battle began with a visibly shiny Zigzagoon.
This is opening QA, not a completed story or Frontier playthrough.

The optional controller supports image captures, emulator checkpoints,
read-only position inspection and a command journal. Emulator checkpoints are
private test aids; actual in-game saving/reloading must also be tested.
