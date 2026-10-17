# Complete Edition permanent progress log

Append dated entries after each meaningful milestone. Keep historical evidence; distinguish source implementation, automated tests and ordinary gameplay.

## 17 October 2026 — live recovery verified

- Read the owner's attached master specification in full.
- Inspected live development and pending branches. Development: `7a15cd7e5d4a964a8c8eef184e9fd1a5324cbe39`; pending: `497700e5c6071b83e87ebaf1b2deead64b651492`.
- Preserved development in `recovery-baseline-20261017`. No resets, force pushes, patch reapplication or gameplay source changes.
- Confirmed the old candidate patch was already reconciled and Embargo's enum mismatch fixed.
- Inspected successful live workflow steps and decoded log for run `38944845308`, job `117121249286`, tested source `057efeb3584cccc90dcfa4b03ae0700012c406e3`.
- Confirmed **5,419 PASS / 5,917 total / zero unexpected failures** and successful native completion footer. Five known failures, 63 assumptions, 421 TODO, seven expected failures and two intentional harness crashes remain visible.
- Flash reward persistence and anti-duplication test passes. Existing earlier run covers all 21 focused families.
- Current head differs from tested source only in QA documentation; production checksum remains `ab7793e8a2f73e56863c88daaf3d726b6ae515a78b8f67aed1f902651f14b040`.
- Updated master spec to version 1.1. Historical baseline and old blocker description retained and clearly marked as historical.
- Normal save remains the recovered Dewford two-badge checkpoint. Do not use Alpha 1 with this save. Slateport save is still missing.
- No new local test run, gameplay progress, feature completion or final release is claimed.

### Environment and immediate continuation

Local Git requests fail with a name-resolution/thread error; PowerShell and Node network attempts also failed. WSL is absent; ARM compiler, make and emulator are not on PATH. GitHub connector access works. No working local checkout or emulator exists in this task.

Resume in an environment able to fetch/build this source and run mGBA, with the verified matching ROM and a copy of the normal save. Verify hashes first; continue Granite Cave/Flash/Steven's Letter using ordinary inputs. Preserve milestone battery saves. Do not fabricate progression or substitute save states.

### Release work still open

1. Complete ordinary story through all Gyms, Elite Four, Steven and Hall of Fame.
2. Exercise Frontier facilities, tournament, visitors, superbosses and defeat/retry paths.
3. Capture/save/reload required starter and legendary events; verify species availability.
4. Exercise competitive services and money/item/full-party/full-PC boundaries.
5. Finish permitted portrait assets and assess presentation/balance through play.
6. Run focused and full final validation, build production ROM and verify BPS round trip.
7. Report hardware timing/audio/flashcart compatibility only if actually tested.

Machine-readable evidence: [2026-10-17 recovery verification](qa/2026-10-17-recovery-verification.json).

## 17 October 2026 — close continuous-validation gap

Source review found that the existing map/event validator was absent from the CI workflow and build script. Added a dedicated CI step before toolchain installation. This validator checks CE placements, manifests, starter/legend capture flags, catalogue gates, quest cycles and graphics coverage. It does not prove whole-map routes or actual story/event execution.

Validation of this CI change is pending until its workflow completes. No game binary source changed. Reviewed service/catalogue/tournament source showed no additional confirmed defect; ordinary gameplay coverage remains required.

### Follow-up evidence during the fresh run

- CI run 39018035474/job 117354056382 passed the newly added event-validation step, parser tests and production build. Full native suite is still in progress.
- Four local parser test methods covering19 scenarios pass with workspace-local TEMP/TMP. Initial test launch failed only because Windows' sandbox temporary directory was unwritable; rerun passed unchanged tests.
- Prior full-log parser recheck confirms 5917/5917 outcomes, zero unexpected failures. All46 Complete Edition-labelled outcomes pass.
- Found installed SDL mGBA0.10.5 outside PATH. Save transfer into this task was denied. Await matching build ZIP and ordinary two-badge save in work/playtest; do not use Alpha1.
- Added the full gameplay checklist with exact locations/gates, source boundaries and18 missing portrait mappings. No additional proven gameplay defect found; no new story progress claimed.

## 17 October 2026 — fresh build, event checks and complete suite PASS

Run [39018035474](https://github.com/Giovannisboss/pokeemerald-expansion-complete-edition-/actions/runs/39018035474), job 117354056382, tested source `f8fa55b0cff7bfee57247ec47098b759a71f29d6`, completed successfully at 09:04:04 UTC. All configured steps passed; the candidate-branch-only focused step is intentionally skipped here and its earlier 21-family evidence remains preserved.

- Production build PASS; SHA-256 unchanged: `ab7793e8a2f73e56863c88daaf3d726b6ae515a78b8f67aed1f902651f14b040`.
- World-event validator PASS: 84 placements, 24 visitors, 12 starters, 29 added legend trails, seventh-badge gates, acyclic quest dependencies and 61 graphics IDs. This does not prove complete route traversal or script gameplay.
- Full native suite PASS: 5419 PASS, 5 KNOWN_FAILING, 63 ASSUMPTION_FAIL, 421 TODO, 7 EXPECTED_FAIL, 2 deliberate expected CRASH; 5917 total, zero unexpected failures.
- Directly inspected the full completion footer and workflow conclusion. Local strict-parser recheck confirms 5917/5917 recorded rows, zero failing footers and correctly classified expected crashes.
- The five existing known failures remain listed in the machine-readable recovery record. No failure markers were changed.
- Owner confirmed the browser was signed out; after sign-in, reports the matching ZIP downloaded. Still awaiting ZIP plus ordinary two-badge save in this task's work/playtest folder. The prior artifact's production ROM matches the fresh build exactly. It contains a QA ROM and checksum/README, not a final release patch.
- Local SDL button helper at work/host-tools/mgba_buttons.py has syntax/--help checks only; no GUI launch/input/gameplay execution yet. Runtime delivery remains unverified.
- Master specification updated to 1.3. Ordinary story, postgame, portraits, save edge cases and final release remain unfinished. No ordinary save was modified.

## 17 October 2026 — ordinary battery recovery and fresh-process reload

- ZIP and original two-badge save received and exact hashes verified; ROM matches fresh CI. Original battery remains unchanged.
- Resolved Windows SDL path issue: ROM basename with session cwd and forward-slash directory overrides enables save discovery and native screenshots. Absolute backslash ROM argument caused the earlier missing Continue; no save conversion required.
- Verified ordinary title/Continue, Dewford Gym, two badges, shiny Marshtomp22 (Mild/Torrent,55/82HP), party and move-summary menus. Normal Win32 key messages target only the owned verified mGBA child; native screenshots show outcomes.
- Completed ordinary in-game SAVE, graceful exit0 and fresh-process reload. Continue shows2:23/two badges; selecting it loads Dewford Gym. Both raw flash slots validate, newest counter16; entire party and PC data match original.
- Original battery SHA256: 914e4b92f1e1df38009a010f44d3b062a64a6c4feef3cbebe3d28bcb47ed19c9.
- Verified milestone battery SHA256: bc254160829475f279e7dc06c7bae9245b43cccdb1d29e2554826a4519dfc828;131088bytes. Working session06 preserved; separate milestone CE_QA_20261017_Dewford_Baseline.sav.
- Evidence: session06 native screenshots19 (Continue2:23),20 (Dewford after fresh reload), earlier7–9 (summary/moves),16–17 (save/field); read-only sector report docs/qa/2026-10-17-baseline-save.json.
- Persistent controller startup must wait for SDL window replacement; reacquire only within same verified child PID. New hold/pulse commands remain unverified. No source game changes, injected flags/items/levels, memory access or savestates.
- Next: leave Gym, heal/check PC, Flash/Steven's Letter in Granite Cave; story/postgame/portraits/release remain pending. No additional user setup required.

## 17 October 2026 — Dewford systems and Granite Cave HM05

- Ordinary play PASS: Gym exit, town/Center transitions, nurse healing (82/82HP), PC opening, Box17-to-Box1 navigation, female Sentret5 withdrawal (19/19HP) and two-member party menu.
- Route106 Fisherman Ned defeated using Rock Tomb; opposing Tentacool12 appeared shiny; normal return to overworld. Marshtomp22 later81/82HP after failed wild catch attempt.
- GraniteCave entry and hiker HM05 award PASS. Fresh-process reload shows both party members and HM05 persists in TM/HM pocket.
- Durable milestone CE_QA_20261017_GraniteCave_HM05.sav: SHA2561295405399a5b6c9fa14fe236a09d0666b4400f06bb7285d999c44ad1360aae8,131088bytes;both slots valid,newest counter19,B1F(4,21),group24/map8. Original unchanged. Working session06 progresses beyond this milestone; counter23 atB1F(25,19).
- Screenshots:40 healed party;46 Box17;51/53 Box1/Sentret;54 withdrawal menu;57 two-member party;60 successful Center save;69 shiny trainer Tentacool;72 faint;74 overworld;76 cave;87 obtained HM05;99 Continue2:41;101 reloaded party;103 HM05 persisted;108/113 B1F circle/menu;119/129/140/146 later ordinary saves.
- Flash teaching/use remains Pending: party Marshtomp/Sentret both NOTABLE; source all_learnables agrees. Cleffa was weakened once then fainted on second Mud-Slap; Abra escaped Great Ball/teleported. No successful catch claimed. Other wild shiny presentations observed.
- Controller basic press/pulse/B+direction and F12/quit observed working, but0.15s direction can only turn and0.3s can take two steps. About0.22s hold/0.4s gap for precision walking; encounters interrupt batches. Verify actual result. Python battery reads work during emulation; Get-FileHash sharing error does not mean save corruption.
- Preserved reusable controller under tools/complete_edition. Static ROM map extraction matched three source Git blob SHA1s, avoiding connector base64 text-normalization corruption. No emulator memory or game-data mutation.
- Rechecked include/config/general.h: GEN_LATEST is GEN_4; no generation config change required.
- Next: ordinary cave traversal/Steven Letter; catch suitable Flash learner normally. Postgame,18 portraits and release patch remain outstanding. Production source unchanged.


## 17 October 2026 — interrupted-session recovery and release patch verification

- Re-read Master Specification version1.5 and inspected live branch HEAD268d999632803e09ddc552d948e3b4fcae5695b7. Preserved its tree and all previous changes; no old patch reapplication, reset or force push.
- Recovered committed progress through Granite Cave HM05 and the persistent Windows controls. The later session06 counter23 save is referenced but not present in this local workspace. Library milestone still resolves; local transfer failed with PermissionError. Computer Use failed to launch its app-server. Local older ROM checksum does not match the verified build, so it was not launched with the newer save.
- Continued release tooling: bounded BPS header, metadata, command and literal decoding to the command section; reject oversized commands and SourceRead outside the input. Previously malformed valid-CRC patches could consume footer bytes or raise IndexError instead of a controlled validation error.
- Added six regression methods covering105 synthetic round trips, every truncation of a generated patch, wrong source, corruption, unterminated numbers, truncated metadata/literals, invalid copy ranges, unsupported modes, target CRC and trailing commands. All six methods pass locally under bundled Python3.12. No retail ROM required or included.
- Added patch-integrity tests to CI before toolchain installation. Remote CI pending for this commit; no new native suite result claimed.
- Game source and production ROM remain unchanged. Last full native suite evidence remains5419PASS/5917outcomes/zero unexpected failures with five documented known failures. Story/Steven Letter, postgame, portraits and final release remain unfinished.


## 17 October 2026 — continue native training boundary coverage

- Owner explicitly deferred ordinary mGBA playthrough and authorized continued GitHub development/build/tests.
- Confirmed CI run39026199175/job117377556313 succeeded, including production compilation, BPS integrity, event placement, parser checks and full native audit. Exact new outcome counts were not independently extracted in this continuation.
- Added four native training regressions: replacement/reduction at exactly510EVs, invalid IV indexes preserving cap/IVs, Egg nature/IV/EV/reset rejection, and invalid party-slot/operation script rejection. These address untested boundaries; no new gameplay defect or production change is claimed.
- New native tests require CI compilation/execution; pending until the workflow reports completion. Previous gameplay checkpoints remain untouched.

### Training boundary CI checkpoint

Run39028497564/job117384104598 at2973b74d8e405ad082714cb35c85f85ec453945c: event validator, six BPS tests, native-log parser checks and production Build all succeeded. Full native regression audit remained in progress at the latest direct job-step query. Available decoded log ended during native-test assembly, with no compiler-error markers in that available content; this is not a completed test result. No verification artifact was available yet. Do not rerun or reapply this change merely because a chat ended: inspect this same run first. Four new tests remain unverified until its completed native log is inspected. Owner has deferred ordinary desktop playthrough; no desktop setup is required to continue GitHub work.


## 17 October 2026 — training boundaries verified; HP regression coverage

- Run39028497564/job117384104598 completed successfully at11:50:05UTC on2973b74d8e405ad082714cb35c85f85ec453945c. Directly inspected completed job, four new PASS lines,5423PASS/5921TOTAL and PASS:full suite footer. Five known failures remain: two disabled Dynamax AI, two Neutralizing Gas, Gen5+ Roost. No failure markers changed.
- Production ROM SHA256 remains ab7793e8a2f73e56863c88daaf3d726b6ae515a78b8f67aed1f902651f14b040. Verification artifact12099323613 digest0458e679e4b80d9b7a5b239d767a76926581b71921b057747a41f4f64a26f7f4.
- Added native HP training coverage for24 parametrized combinations: Pikachu/Shedinja; nature,HP IV,HP EV,EV reset; fainted,oneHP,healthy. Checks no revival,HP bounds,appropriate maxHP recalculation,identity and shininess.
- Added --ce-only mode to existing test runner and a focused native CI step before full suite. Separate log directory preserves both focused and full evidence. Uses the same strict result classifier and ARM object validation. New native test/runner changes pending their CI execution.
- No production game changes. Ordinary playthrough remains explicitly deferred by owner. Artwork and final ordinary-gameplay certification remain unfinished.

### Reclassified completed training audit

Timestamp-stripped native rows and summary footers from completed run39028497564 were locally passed through the repository strict parser:5921/5921 complete,5423PASS,zero unexpected failures,two green expected crashes,zero failing footers. All50 Complete Edition outcomes pass. Saved docs/qa/2026-10-17-training-boundaries.json and refreshed the status-page lead; historical evidence is retained. The HP follow-up remains pending CI.

### HP training focused check passed

Run39030540953/job117389924632 at a18692567ed17b4a1cef13fec1cf253167c72ae9: production Build passed at12:00:21UTC; new Complete Edition native regressions step passed at12:05:25UTC. World-event,BPS and parser checks also passed. Full native audit is running. Exact HP result rows and final outcome counts will be inspected after the completed job log becomes available; available partial log still ended during assembly. No final full-suite result or ordinary-gameplay completion is claimed yet.
