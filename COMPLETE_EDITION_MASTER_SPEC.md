# Pokémon Emerald: Complete Edition
## Master Specification & Development Recovery Handover
**Version:** 1.5 — 17 October 2026  
**Project owner:** Giovannisboss  
**Status:** Advanced alpha; completion and final verification outstanding

---

## 1. Project mission

Produce a complete, dependable, playable Pokémon Emerald ROM hack featuring all 493 Generation 1–4 Pokémon, guaranteed shinies, expanded trainer battles, competitive training tools and substantial optional postgame content.

Preserve the original Hoenn adventure, Emerald identity and Battle Frontier.

The project must be finished through actual implementation, compilation, gameplay testing, bug fixing and release verification—not merely planning or passing a partial automated test suite.

The owner prefers autonomous development, minimal interruptions, phone-based management and only crucial questions.

## Current recovery state — 17 October 2026

Read this section before acting on the historical handover below.

- Recovery-start development HEAD verified: `7a15cd7e5d4a964a8c8eef184e9fd1a5324cbe39`.
- Recovery snapshot: `recovery-baseline-20261017`, pointing to that exact commit.
- Pending branch remains `497700e5c6071b83e87ebaf1b2deead64b651492`; preserve it as historical evidence.
- Pending fixes were already reconciled at `adb01b50634e49c0d3dfbbd59d6d787dd549424b`. Do not reapply the old patch.
- Embargo compilation blocker is already fixed: `ShouldUseItem(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT))`.
- Latest completed full audit: fresh run [39018035474](https://github.com/Giovannisboss/pokeemerald-expansion-complete-edition-/actions/runs/39018035474), job `117354056382`, source `f8fa55b0cff7bfee57247ec47098b759a71f29d6`, completed successfully on 17 October 2026. Prior run `38944845308` independently passed the same counts at `057efeb3584cccc90dcfa4b03ae0700012c406e3`.
- Directly inspected job log and successful steps verify **5,419 PASS, 5 known failures, 63 assumption skips, 421 TODO, 7 expected failures and 2 deliberate harness crashes: 5,917 outcomes, zero unexpected failures**. Footer: `PASS: full suite`.
- All 21 affected candidate families passed in earlier run `38942000064` at `adb01b5...`. The later full runs intentionally skip that branch-specific focused step and run the full suite.
- Additional passing test: pending tournament prize survives flash reload; saving a claim prevents duplication.
- Verified CI production ROM SHA-256: `ab7793e8a2f73e56863c88daaf3d726b6ae515a78b8f67aed1f902651f14b040`.
- The fresh CI rebuild produced exactly the same production ROM checksum. Later handover/checklist commits contain documentation only; no production game source changed in this continuation.
- Five known failures: two disabled Dynamax AI cases, two Neutralizing Gas interactions, Gen5+ Roost rounding. These remain explicit limitations; zero unexpected failures does not mean zero known failures.
- Latest recovered normal save remains Dewford Gym after Brawly. Later Slateport progress has no recovered save. **Never pair the Alpha 1 ROM with this save**: incompatibility was reproduced previously. Back up the battery file before using the current Alpha 2.5.1 build.
- Ordinary story/postgame completion, remaining portraits and release QA remain outstanding.

Permanent continuation record: `docs/COMPLETE_EDITION_PROGRESS_LOG.md`.
Latest audit details: `docs/qa/2026-10-17-recovery-verification.json`.
Detailed locations and pending ordinary-play checks: `docs/COMPLETE_EDITION_GAMEPLAY_QA.md`.

### Fresh validation in this continuation

- Added the previously omitted world-event validator to CI at `f8fa55b0cff7bfee57247ec47098b759a71f29d6`.
- Fresh run `39018035474`, job `117354056382`: world-event validation, native-log classification, production build and full native suite all passed. Directly inspected the complete log and successful workflow conclusion. Locally re-ran the strict parser on its native results: 5,917/5,917 outcomes, zero unexpected failures, two correctly classified expected crashes and zero failing summary footers.
- Locally ran four result-parser regression methods (19 scenarios): PASS after placing TEMP/TMP in the writable task folder. Reclassified the prior CI log with the same parser: complete 5,917 outcomes, zero unexpected failures.
- All 46 Complete Edition-labelled outcomes in the prior full log pass; the fresh full run preserves the same suite totals. Native results are not an ordinary-playthrough result.

### Ordinary gameplay recovered and save/reload verified

The matching ZIP and original two-badge save are now present locally. ZIP SHA-256: `850fc454678a920914892c4fb39aa95f86483ae323133b8d6624d22b895b5767`. Its ROM matches the fresh CI production checksum above. Original battery SHA-256: `914e4b92f1e1df38009a010f44d3b062a64a6c4feef3cbebe3d28bcb47ed19c9`; preserve it unchanged.

mGBA SDL 0.10.5 successfully loads this save from a separate working copy. On Windows launch with the ROM **basename** and session directory as cwd; use forward slashes for save/screenshot directory overrides. Passing an absolute backslash ROM argument prevented save discovery and screenshots. This was a host path issue, not save corruption; no save conversion was required.

Observed through ordinary controls and native screenshots: custom title, Continue with two badges, Dewford Gym, shiny male Marshtomp level 22 with 55/82 HP, Mild nature, Torrent and Tackle/Rock Tomb/Mud-Slap/Water Gun. Read-only inspection confirms one stored Pokémon in primary PC storage, matching the original. Ordinary in-game SAVE completed. After graceful emulator closure and a fresh process, Continue showed 2:23 and two badges; selecting it loaded Dewford Gym successfully. Both flash slots have valid checksums and signatures; newest counter is 16. Party and PC bytes remain identical to the original checkpoint.

Verified new battery SHA-256: `bc254160829475f279e7dc06c7bae9245b43cccdb1d29e2554826a4519dfc828` (131088 bytes). Current working copy: `work/playtest/session-06/CE_20261016_Verified.sav`. Milestone copy: `CE_QA_20261017_Dewford_Baseline.sav`. Normal input and native screenshots work through a persistent host process owning the hidden SDL child. Refresh the current SDL window within that same verified PID; SDL replaces its startup window. No memory access, cheats, injected progression or savestates were used. New simultaneous-hold/pulse commands are not yet gameplay-verified.

**Baseline checkpoint next task (now progressed):** Dewford exit, healing, PC withdrawal and HM05 acquisition have subsequently passed; see the Granite Cave milestone below. Steven's Letter remains pending. Story completion, postgame, portraits and final release patch remain outstanding. No further file transfer is required from the owner.

Local network/build limitations remain: Git/PowerShell cannot resolve GitHub, WSL is absent and local ARM compiler/make are unavailable. GitHub connector access and fresh CI builds work. Do not repeat reconciliation or reset newer commits because of these local limitations.

### Latest ordinary-play milestone — Granite Cave

Completed ordinary gameplay since Dewford: Gym exit, Pokémon Center healing to 82/82 HP, PC opening, Box17-to-Box1 navigation, withdrawal of female Sentret level5 (19/19HP), Route106 Fisherman Ned victory, cave entry, and the hiker awarding HM05. Shiny trainer Tentacool and wild Makuhita/Aron/Cleffa/Abra were observed. A fresh process reloaded the cave save with both party members; HM05 remained in the TM/HM pocket.

Durable milestone: `CE_QA_20261017_GraniteCave_HM05.sav`, SHA256 `1295405399a5b6c9fa14fe236a09d0666b4400f06bb7285d999c44ad1360aae8`, 131088bytes. Both slots pass all sector checksums/signatures; newest counter19 is GraniteCave_B1F at(4,21), mapgroup24/map8. Original battery remains unchanged. The working session06 save advances beyond this separately preserved milestone; inspect its newest valid slot before resuming. Later counter23 was at B1F(25,19).

**Next:** finish ordinary cave traversal and Steven's Letter. Flash teaching/use remains pending: neither Marshtomp nor Sentret is compatible, matching the current source learnability data. Cleffa fainted during a weakening attempt; Abra escaped a Great Ball and teleported. No successful capture or Flash use is claimed. Three Poké Balls and one Great Ball remained after these attempts. Do not inject a compatible Pokémon or items.

Reusable Windows ordinary-input controller is preserved in `tools/complete_edition/mgba_session.py` with `mgba_buttons.py`. Run the persistent runner from the task checkout using an existing verified ROM/save session; it never recopies saves. Basic press/pulse/simultaneous B+direction, native screenshot and graceful closure are screenshot-observed. Individual posted messages still require visual result confirmation. For precision walking use about0.22s hold/0.4s gap;0.15s can turn without stepping,0.3s can take two steps. Encounters interrupt movement batches. Use normal in-game SAVE, then read the battery file to confirm position rather than assuming requested steps occurred. Python read_bytes can read the save with the emulator open; PowerShell Get-FileHash can fail on sharing mode.

Static map data fetched through the connector's base64 file route may be altered by text decoding when high bytes occur. Three cave map blocks were instead recovered read-only from the verified ROM and checked against their exact Git blob SHA1s; do not use a binary map unless its source blob hash matches. This is static ROM/source inspection, not emulator-memory access. The source generation default was rechecked: `GEN_LATEST GEN_4` in include/config/general.h; many individual settings legitimately refer to GEN_LATEST.

Story completion, remaining portraits, postgame systems and final release patch remain unfinished. The CI production source and checksum are unchanged.

## 2. Repository and source control

**Repository:**  
https://github.com/Giovannisboss/pokeemerald-expansion-complete-edition-

**Engine:** rh-hideout/pokeemerald-expansion

**Primary development branch:** `complete-edition-development`

**Last recorded development HEAD:**  
`ff0dce502fda88a723552fc6db3ecca0d88f3b20`

This SHA is historical, not guaranteed to be the current HEAD. Always inspect the live remote before modifying code.

**Preserved candidate-fixes branch:**  
`handoff-pending-fixes-20261016`

**Handover commit:**  
`497700e5c6071b83e87ebaf1b2deead64b651492`

**Patch base:**  
`09265b088da9707260782356a7ea7885dd9033bb`

Preserved handover files:

- `docs/qa/2026-10-16-pending-fixes.patch`
- `docs/qa/2026-10-16-completed-baseline.json`

The patch contains unvalidated candidate changes. Review and reconcile it with the current development branch before applying anything. Never overwrite newer work.

## 3. Core gameplay specification

### Pokémon availability

- All 493 Pokémon from Generations 1–4 obtainable in one save.
- No trading or external event distributions required.
- All starter evolution families available through special locations or appropriate in-game encounters.
- All Generation 1–4 legendary and mythical Pokémon obtainable through in-game encounters or events.
- Species from all four generations distributed naturally throughout Hoenn, including the early adventure.
- Every Pokémon shiny: wild, trainers, starters, gifts, eggs, legendaries and mythicals.
- Shiny status must be genuine and persist correctly through saving, evolution, trading where supported and battles.

### Battle mechanics

- Generation 4 physical/special move split.
- Generation 4 mechanics, moves and abilities as the target.
- No Fairy type.
- No Dynamax or Gigantamax, for either players or trainers.
- Slightly harder main adventure, without extreme difficulty.
- Preserve the original Emerald storyline and Battle Frontier.
- Steven Stone is Champion.
- Keep competitive postgame encounters considerably harder than ordinary story battles.

Specific Gen 4 moves or abilities may be omitted only if genuinely necessary to resolve blocking technical problems; preserve the physical/special split.

### Optional Gym Leaders

All 24 Kanto, Johto and Sinnoh Gym Leaders appear at appropriate in-world locations around Hoenn.

Their battles must be optional, not progression gates. Repeatability and suitable team difficulty are required.

### Pokémon World Tournament

A dedicated postgame facility featuring all 32 regional Gym Leaders from Kanto, Johto, Hoenn and Sinnoh.

Support repeatable competitive battles and appropriate tournament rewards.

Tournament prizes must never silently disappear if the player's bag is full.

### Postgame superbosses

Red, Blue, Silver and Gold must be available as repeatable encounters.

Teams should feature competitive movesets, items, EVs, IVs, natures, appropriate AI and high difficulty.

Do not substitute arbitrary unfair mechanics for competitive challenge.

## 4. Training and quality-of-life systems

- Nature-changing service, preferably accessible through Pokémon Centres.
- Bottle Caps for maximising individual IVs.
- Gold Bottle Caps for maximising all IVs.
- EV allocation and reset services.
- Maximum 252 EVs per stat and 510 total.
- Practical access to competitive preparation without excessive grinding.
- Reusable TMs and trade-free evolutions where specified in the original design.
- Birch's research catalogue unlocks after the seventh Gym; unlocking does not necessarily mean every catalogue reward is immediately available.
- 17 PC storage boxes, providing 510 slots.

Verify money/item transactions, stat recalculation, persistence and boundary conditions.

## 5. Presentation

**Game title:** Pokémon Emerald: Complete Edition

Use the approved visual direction for the custom title screen, adapted to actual GBA hardware limitations.

Maintain readable graphics, correct palettes, reliable title-screen transitions and the original game's general aesthetic.

Source audit confirms 18 missing dedicated battle portraits: all 16 Johto/Sinnoh leaders, Gold and Silver. The leaders use substitutes in both visitor and tournament teams. Correct dedicated assets were not found in the current source asset directories/registries. The exact mappings are recorded in the gameplay QA checklist.

An earlier portrait-generation attempt was rejected by an automatic approval review. Do not circumvent that restriction. Use permitted assets or leave the limitation clearly documented.

## 6. Historical automated testing baseline

The recorded baseline from the Dynamax-disabled source completed with:

| Outcome | Count |
|---|---:|
| PASS | 5,400 |
| Known failures | 16 |
| Assumption skips | 63 |
| TODO | 421 |
| Expected failures | 7 |
| Expected crashes | 2 |
| Unexpected failures | 0 |
| **Total** | **5,909** |

The report states that the baseline completed successfully.

These are baseline results, not evidence that the pending candidate patch passed.

The 421 TODO outcomes represent upstream test gaps, not necessarily 421 missing Complete Edition features.

Two known failures concern upstream Dynamax AI while Dynamax is disabled.

## 7. Historical pending fixes and compilation blocker (resolved)

The preserved candidate patch included work concerning:

- Helping Hand AI.
- Beat Up, Justified and Protect interactions.
- Simulated terrain.
- Ability fixes and test fixtures.
- Roost, Embargo and Sleep Clause fixtures.
- Stricter test-result reporting.
- Tournament prize recovery.

A specific tournament bug was identified: if the Items pocket is full, an earned Gold Bottle Cap could be lost.

The candidate solution uses a persistent pending-prize flag, with collection after making bag space and protection against duplicate claims.

The candidate production ROM reportedly compiled, but focused tests stopped at a test compilation error:

`test/battle/move_effect/embargo.c`

`ShouldUseItem` expects `enum BattlerId`, but the fixture passes `B_POSITION_OPPONENT_LEFT`, which belongs to `enum BattlerPosition`.

This mismatch is now fixed and the affected families and full suite pass, as recorded in the current recovery section. Preserve the details here as historical context.

Do not claim the candidate patch is validated before those tests pass.

Avoid global spread-move target-order changes that previously caused regressions.

## 8. Ordinary gameplay save and playthrough

**Latest recovered save:**  
`CE_QA_Alpha25_TwoBadges.sav`

Recorded state:

- Dewford Gym, after defeating Brawly.
- Two Gym badges.
- Shiny Marshtomp, level 22.
- Sentret stored in Box 1.
- Next objectives: Granite Cave, Flash and Steven's Letter.

A later Slateport playthrough is documented in:

`docs/qa/2026-10-16-alpha-2-5-slateport.json`

However, the corresponding ordinary save was not recovered in the previous handover.

If a newer valid save exists, verify and use it. Otherwise continue from the two-badge checkpoint.

**Testing integrity rules:**

- Use normal gameplay controls.
- Use ordinary battery saves.
- Verify saving and reloading.
- Do not inject story flags, levels, Pokémon, items or progression.
- Do not substitute emulator states for ordinary save verification.
- Preserve milestone saves durably.

## 9. Remaining verification

### Main adventure

Complete and verify the story from the latest reliable save through all remaining Gyms, Elite Four, Steven Champion battle, Hall of Fame and postgame unlocks.

Test progression gates, map transitions, rival encounters, HM requirements and save/reload behaviour.

### Postgame

Verify all seven Battle Frontier facilities, visiting Gym Leaders, tournament modes, repeatable superbosses, starter encounters and legendary/mythical captures.

### Systems and edge cases

Test nature changes, IV training, EV services, transaction costs, insufficient funds, full bags, storage limits, repeat rewards, shiny persistence and save compatibility.

### Release quality

Run focused regression tests and a complete final suite.

Compile the final production ROM and verify it in a suitable emulator.

Real-hardware timing, audio and flashcart compatibility remain unverified unless subsequently tested.

Never declare the project finished solely because the ROM compiles or a partial test suite passes.

## 10. Rules for future development sessions

1. Inspect current GitHub branches, commits and outstanding changes before editing.
2. Preserve all existing implementation and test evidence.
3. Never blindly overwrite or reset another session's work.
4. Use the existing code as the starting point; do not rebuild completed systems unnecessarily.
5. Preserve the verified reconciled fixes; do not reapply the historical patch or repeat its resolved compilation blocker.
6. Run focused tests, followed by the full test suite.
7. Continue ordinary story gameplay and preserve valid save checkpoints.
8. Audit every requested feature against actual game behaviour.
9. Keep commits small, traceable and recoverable.
10. Report verified successes, failures and untested areas separately.
11. Use parallel agents where appropriate, but coordinate changes to shared files.
12. Ask the owner only crucial questions.
13. Do not commit copyrighted retail ROMs to the public repository.
14. Maintain a durable progress log and update this master specification after significant milestones.

## 11. Definition of done

Complete Edition is finished only when:

- All required features are implemented.
- A clean production ROM compiles.
- The final automated test suite is complete, with no unexplained unexpected failures.
- The main story is successfully completed through ordinary gameplay.
- The Battle Frontier and major postgame content are verified.
- Required species are demonstrably obtainable.
- Save/reload, storage, transactions and repeatable encounters behave correctly.
- A verified playable build and distributable patch are produced.
- Any remaining limitations are clearly documented.

**Recovery priority:** Protect existing work first. Reconcile candidate fixes second. Resume validation and gameplay third. Finish outstanding features and release only after those foundations are dependable.