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
