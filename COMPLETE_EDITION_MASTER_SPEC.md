# Pokémon Emerald: Complete Edition
## Master Specification & Development Recovery Handover
**Version:** 1.2 — 17 October 2026  
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

- Live development HEAD verified: `7a15cd7e5d4a964a8c8eef184e9fd1a5324cbe39`.
- Recovery snapshot: `recovery-baseline-20261017`, pointing to that exact commit.
- Pending branch remains `497700e5c6071b83e87ebaf1b2deead64b651492`; preserve it as historical evidence.
- Pending fixes were already reconciled at `adb01b50634e49c0d3dfbbd59d6d787dd549424b`. Do not reapply the old patch.
- Embargo compilation blocker is already fixed: `ShouldUseItem(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT))`.
- Latest completed full audit: run [38944845308](https://github.com/Giovannisboss/pokeemerald-expansion-complete-edition-/actions/runs/38944845308), job `117121249286`, source `057efeb3584cccc90dcfa4b03ae0700012c406e3`.
- Directly inspected job log and successful steps verify **5,419 PASS, 5 known failures, 63 assumption skips, 421 TODO, 7 expected failures and 2 deliberate harness crashes: 5,917 outcomes, zero unexpected failures**. Footer: `PASS: full suite`.
- All 21 affected candidate families passed in earlier run `38942000064` at `adb01b5...`. The newer full run intentionally skips that branch-specific focused step and runs the full suite.
- Additional passing test: pending tournament prize survives flash reload; saving a claim prevents duplication.
- Verified CI production ROM SHA-256: `ab7793e8a2f73e56863c88daaf3d726b6ae515a78b8f67aed1f902651f14b040`.
- Development HEAD differs from the latest tested source only in two QA documentation files. This continuation has not built a new ROM.
- Five known failures: two disabled Dynamax AI cases, two Neutralizing Gas interactions, Gen5+ Roost rounding. These remain explicit limitations; zero unexpected failures does not mean zero known failures.
- Latest recovered normal save remains Dewford Gym after Brawly. Later Slateport progress has no recovered save. **Never pair the Alpha 1 ROM with this save**: incompatibility was reproduced previously. Back up the battery file before using the current Alpha 2.5.1 build.
- Ordinary story/postgame completion, remaining portraits and release QA remain outstanding.

Permanent continuation record: `docs/COMPLETE_EDITION_PROGRESS_LOG.md`.
Latest audit details: `docs/qa/2026-10-17-recovery-verification.json`.
Detailed locations and pending ordinary-play checks: `docs/COMPLETE_EDITION_GAMEPLAY_QA.md`.

### Fresh validation in this continuation

- Added the previously omitted world-event validator to CI at `f8fa55b0cff7bfee57247ec47098b759a71f29d6`.
- Fresh run `39018035474`, job `117354056382`: world-event validation, native-log classification and production build have passed; the full native suite is running. Do not describe this run as complete until its footer, counts and workflow conclusion are checked.
- Locally ran four result-parser regression methods (19 scenarios): PASS after placing TEMP/TMP in the writable task folder. Reclassified the prior CI log with the same parser: complete 5,917 outcomes, zero unexpected failures.
- All 46 Complete Edition-labelled native outcomes in that prior full log pass. This is still not an ordinary-playthrough result.

### Execution blocker in this continuation

The current Windows execution host cannot resolve GitHub from local Git/PowerShell/Node requests; `git ls-remote` fails with `getaddrinfo() thread failed to start`. GitHub connector reads and source writes work. WSL is not installed; no ARM compiler or make is available on PATH. mGBA 0.10.5 was subsequently found at `C:\\Program Files\\mGBA\\mgba-sdl.exe`, outside PATH. No local source checkout, matching ROM or running emulator has been recovered here. The normal-save transfer was denied by the local execution environment. The owner has been asked to place the matching build ZIP and two-badge save in this task's `work/playtest` directory; verify exact hashes before launching.

This is an execution-environment limitation, not a game defect. A working build/emulation environment is required for ordinary gameplay and fresh local validation. Existing successful CI logs were inspected; they must not be described as new tests run by this chat. Do not repeat the patch reconciliation merely because local cloning is unavailable. No gameplay progress or new release patch has been produced in this continuation.

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
5. Fix the immediate test blocker and validate the pending patch.
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