# Complete Edition ordinary-gameplay QA checklist

Source snapshot: `f8fa55b0cff7bfee57247ec47098b759a71f29d6`. Prepared 2026-10-17 from live GitHub source. This document is a plan: **every new gameplay check below is Pending; no gameplay was executed while preparing it.**

## Evidence boundaries and starting point

Fresh CI run 39018035474 at this source snapshot has since completed: production build, event validator and full suite PASS, with 5419 passes and zero unexpected failures across 5917 outcomes. Its production ROM checksum remains ab7793e8a2f73e56863c88daaf3d726b6ae515a78b8f67aed1f902651f14b040. This changes no Pending ordinary-gameplay checks.

Prior native evidence: reconciliation run 38942000064/job 117111681207 passed the production build, 21 affected families and the full 5,916-outcome audit. The later run 38944845308/job 117121249286 passed 5,917 outcomes, including a tournament-prize flash reload test: 5,419 PASS, seven expected failures, two deliberate harness crashes, five known failures, 63 assumption skips and 421 TODOs. These counts describe those historical source snapshots, not a new run on the source snapshot named above.

Previously recovered ordinary battery save: Dewford after Brawly, two badges, shiny level-22 Marshtomp, Sentret in BOX1. The later historical Slateport report lacks its matching recovered save. Validate the current save/ROM pair before accepting that position. The old Alpha1 ROM is incompatible with the expanded save format. Prior source/native verification of factories, flags, party generation and 510 storage slots does not establish ordinary menu, travel, capture or story completion.

This checklist uses normal controller inputs and in-game saves only. No injected badges, flags, levels, items, money, Pokemon, warps or memory writes. **No emulator savestates for progress, recovery or evidence.** Read-only observation and screenshots may support a check; the game must cause every state change. Full-pocket and storage stress cases must use ordinarily obtained items/Pokemon; keep them on labelled copies of ordinary battery saves.

## Recording and checkpoint procedure

For each check record ID, ROM SHA-256/source commit, input save SHA-256, emulator/version, UTC start/end, actions, observed result, output save SHA-256 and screenshot/journal filenames. Mark Pass only after observation; otherwise retain Pending, or mark Fail/Blocked with a reproducible reason. Never infer Pass from native tests, static code or a historical chat claim.

At each milestone:
1. Reach a safe field position and record map, coordinates if available, badges, key story items, party species/levels/HP/moves, money, Dex counts and notable PC slots.
2. Use the game's SAVE menu, wait for its completion text and return to the field.
3. End the emulator cleanly so battery flash is flushed. Copy the ordinary `.sav` to a unique milestone filename; preserve its original bytes and record SHA-256. Emulator RTC trailers may make files slightly larger than 128 KiB: record actual byte length.
4. Start a fresh emulator process with the same verified ROM and copied battery save under the matching ROM basename. Use Continue; never load a savestate.
5. Confirm the recorded party, location, badges, inventory, Dex and PC contents. Move normally, enter/leave a menu and finish one safe field transition. Save/reload again if the test changes persistent state.
6. Record failures before retrying; branch from a labelled ordinary save copy only when necessary. Preserve the canonical furthest verified story save.

## Story route and durable milestones

Each row is Pending for this takeover, including rechecks of historically reported material. Walk routes normally and observe required dialogue, movement, trainer battles, move-learning/evolution screens and healing. Side content must not be required for story progression.

| ID | Ordinary milestone and evidence | Status |
| --- | --- | --- |
| M00 | Confirm recovered Dewford/two-badge save, Marshtomp and BOX1 Sentret; fresh-process reload | Pending |
| M01 | Obtain Flash, traverse Granite Cave, deliver Steven's Letter, receive his reward; save/reload | Pending |
| M02 | Briney travel to Slateport, deliver Devon Goods, complete museum/Aqua story and harbour access | Pending |
| M03 | Route110 rival battle, Mauville/Wally events, Wattson and Dynamo Badge/TM; normal exits | Pending |
| M04 | Rock Smash progression, Meteor Falls/Chimney Aqua/Magma story, Flannery and Heat Badge | Pending |
| M05 | Norman and Balance Badge; Surf acquisition and use, original badge/HM gates retained | Pending |
| M06 | Weather Institute rescue and Castform gift, Route119 rival, Fortree/Devon Scope, Winona/Feather Badge | Pending |
| M07 | Mt.Pyre, Lilycove and hideout, Mossdeep, Tate/Liza and Mind Badge; catalogue unlock before Champion | Pending |
| M08 | Dive, Seafloor Cavern, weather crisis/Sootopolis, Sky Pillar and Rayquaza story; no softlocks | Pending |
| M09 | Juan/Rain Badge, Waterfall, Victory Road/Wally, Elite Four and Steven as Champion | Pending |
| M10 | Credits, Hall of Fame, postgame return/home events and fresh normal-save continuation | Pending |
| M11 | Access Battle Frontier normally; complete tournament, superboss, facility and legendary checks below | Pending |

- [ ] Pending - optional fresh-save opening smoke: title music/art, A/Start, New Game, truck/clock/Birch rescue, shiny starter preview, first rival, Dex and running shoes.
- [ ] Pending - early wild encounters show Kanto/Johto/Sinnoh species without a badge/Champion gate: Route101 Pidgey/Sentret/Starly/Bidoof; log actual sightings/captures.
- [ ] Pending - wild, trainer, gift, starter, Egg/hatch and legendary shininess observed; trainer/wild battle exit restores NPC graphics safely.
- [ ] Pending - reusable TM: teach, retain item, teach again to another eligible Pokemon; normal HM usage and field gates.
- [ ] Pending - local trade evolutions through ordinary leveling/held items, item consumed where appropriate, evolution screen and post-evolution moves/stats persist.
- [ ] Pending - physical/special split seen in representative battles; no player/trainer Dynamax/Gigantamax option or activation.
- [ ] Pending - ordinary blackout at a safe checkpoint returns to the expected healing location; party recovery and subsequent field controls work.

## Visiting leaders: all 24 independent, optional and repeatable

Coordinates below are **authored map-grid positions**, zero-based `x,y` inside the named source map, not screen pixels. Elevation is the map-object field. The named badge must be owned; ordinary story, HM and terrain access requirements still apply. Low-tide Shoal Cave locations need the correct clock/tide.

For **each row** execute: reach by normal travel; verify sprite/dialogue; check pre-badge refusal when reachable on an earlier ordinary save; decline and cancel without starting battle; accept, verify named three-Pokemon shiny team; win and safely regain field controls; re-challenge to prove replay; save/reload and repeat interaction. Record loss/whiteout/recovery on a labelled ordinary-save branch for each distinct map/battle-return path where feasible. A gate that cannot be reached early is Blocked for negative gameplay coverage, not Pass.

| ID | Leader | Source map | Object position | Battle gate | Gameplay |
| --- | --- | --- | --- | --- | --- |
| V01 | BROCK | `RusturfTunnel` | (4, 8), elev 3 | Badge 1 | Pending |
| V02 | MISTY | `Route109` | (13, 6), elev 3 | Badge 2 | Pending |
| V03 | LT  SURGE | `NewMauville_Inside` | (32, 35), elev 3 | Badge 3 | Pending |
| V04 | ERIKA | `Route104` | (5, 20), elev 3 | Badge 4 | Pending |
| V05 | KOGA | `Route119` | (33, 111), elev 3 | Badge 5 | Pending |
| V06 | SABRINA | `MtPyre_4F` | (10, 3), elev 3 | Badge 6 | Pending |
| V07 | BLAINE | `FieryPath` | (25, 3), elev 3 | Badge 7 | Pending |
| V08 | GIOVANNI | `Route111` | (19, 60), elev 3 | Badge 8 | Pending |
| V09 | FALKNER | `Route104` | (32, 44), elev 3 | Badge 1 | Pending |
| V10 | BUGSY | `PetalburgWoods` | (14, 7), elev 3 | Badge 2 | Pending |
| V11 | WHITNEY | `Route117` | (51, 7), elev 3 | Badge 3 | Pending |
| V12 | MORTY | `MtPyre_Exterior` | (19, 12), elev 3 | Badge 4 | Pending |
| V13 | CHUCK | `GraniteCave_1F` | (34, 4), elev 3 | Badge 5 | Pending |
| V14 | JASMINE | `Route118` | (9, 8), elev 3 | Badge 6 | Pending |
| V15 | PRYCE | `ShoalCave_LowTideIceRoom` | (16, 11), elev 3 | Badge 7 | Pending |
| V16 | CLAIR | `MeteorFalls_1F_1R` | (4, 5), elev 3 | Badge 8 | Pending |
| V17 | ROARK | `GraniteCave_B1F` | (11, 2), elev 3 | Badge 1 | Pending |
| V18 | GARDENIA | `Route116` | (65, 12), elev 3 | Badge 2 | Pending |
| V19 | MAYLENE | `JaggedPass` | (14, 38), elev 3 | Badge 3 | Pending |
| V20 | WAKE | `DewfordTown` | (3, 5), elev 3 | Badge 4 | Pending |
| V21 | FANTINA | `MtPyre_3F` | (3, 2), elev 3 | Badge 5 | Pending |
| V22 | BYRON | `AbandonedShip_Deck` | (11, 6), elev 3 | Badge 6 | Pending |
| V23 | CANDICE | `ShoalCave_LowTideInnerRoom` | (30, 27), elev 3 | Badge 7 | Pending |
| V24 | VOLKNER | `Route110` | (11, 68), elev 3 | Badge 8 | Pending |

## Starter sites: all twelve capture-only completions

For **each row**: normal travel and badge gate, decline, encounter at stated level/shiny; flee or KO and return to confirm retry; then capture with ordinarily purchased Pokeballs. Confirm party/PC placement and Dex entry, object removal only after capture, and persistence after fresh-process battery reload. On a full-party branch verify capture is sent to the selected PC box. With no room anywhere, verify safe refusal/no lost encounter. Test loss/recovery on a preserved battery-save branch without changing the canonical completed capture.

| ID | Starter | Source map | Object position | Level | Minimum gate | Gameplay |
| --- | --- | --- | --- | --- | --- | --- |
| S01 | BULBASAUR | `PetalburgWoods` | (16, 36), elev 3 | 10 | Badge 1 | Pending |
| S02 | CHARMANDER | `FieryPath` | (26, 34), elev 3 | 20 | Badge 3 | Pending |
| S03 | SQUIRTLE | `Route109` | (12, 8), elev 3 | 15 | Badge 2 | Pending |
| S04 | CHIKORITA | `Route117` | (53, 6), elev 3 | 18 | Badge 3 | Pending |
| S05 | CYNDAQUIL | `JaggedPass` | (13, 7), elev 3 | 22 | Badge 4 | Pending |
| S06 | TOTODILE | `Route114` | (29, 7), elev 3 | 20 | Badge 3 | Pending |
| S07 | TREECKO | `Route119` | (8, 34), elev 4 | 25 | Badge 5 | Pending |
| S08 | TORCHIC | `Route112` | (11, 38), elev 3 | 18 | Badge 3 | Pending |
| S09 | MUDKIP | `Route120` | (4, 55), elev 3 | 25 | Badge 5 | Pending |
| S10 | TURTWIG | `Route123` | (22, 8), elev 3 | 30 | Badge 6 | Pending |
| S11 | CHIMCHAR | `MeteorFalls_1F_1R` | (9, 4), elev 3 | 25 | Badge 4 | Pending |
| S12 | PIPLUP | `ShoalCave_LowTideEntranceRoom` | (6, 4), elev 3 | 30 | Badge 7 | Pending |

## Research catalogue and all 493 availability

Researcher: Birch's Lab in Littleroot, source map `LittlerootTown_ProfessorBirchsLab`, object (3,8), elevation 3.

- [ ] Pending - before Mind Badge, Research encounters refuses; habitat advice, evolution supplies and Legendary trails hints remain usable.
- [ ] Pending - immediately after Mind Badge and before Hall of Fame, regional menus work; choose first/last entries in every region and cancel at every level.
- [ ] Pending - menus cover Kanto1-151, Johto152-251, Hoenn252-386 and Sinnoh387-493; no skipped or cancel-colliding entry.
- [ ] Pending - repeatable level50 wild research battles require own balls; flee/KO/loss permits retry; captures enter Dex/party/PC normally.
- [ ] Pending - maintain an acquisition ledger for National Dex1-493: species, method, map, capture/hatch/evolution evidence, current party/box/slot, normal-save checkpoint.
- [ ] Pending - obtain all 493 on the same ordinary save and retain all 493 simultaneously; distinct forms do not replace missing base species.
- [ ] Pending - confirm a catalogue-caught legend does not falsely complete its linked world-trail prerequisite; complete that trail normally afterward.
- [ ] Pending - ordinary evolution shop purchases, affordability/refusal, Bag capacity and held-item evolution consumption.
- [ ] Pending - breeding/daycare produces shiny Eggs and hatchlings without losing parent identity or taught moves unexpectedly.

## Legendary world encounters

**Every added trail below requires Mind Badge**, even rows also listing Hall of Fame or prerequisites. Prerequisites mean captured **world trails**, not catalogue ownership. Normal story/HM/tide/Safari access applies. Readiness and menu generation previously have native coverage; every travel/capture interaction below remains Pending.

For each added trail: check hint, reach object normally, exercise unavailable dialogue where a gate is unmet, decline, battle, verify level/shiny, flee/KO retry, capture, object/completion persistence after save and fresh process. Test each linked prerequisite while one required trail remains missing, using naturally progressed saves. For Uxie explicitly inspect Safari entry, battle/capture controls, ball handling, step/exit behavior and safe return.

| ID | Pokemon | Source map | Object position | Level | Additional gates beyond Mind Badge | Gameplay |
| --- | --- | --- | --- | --- | --- | --- |
| L01 | ARTICUNO | `ShoalCave_LowTideIceRoom` | (14, 10), elev 3 | 50 | Mind Badge only | Pending |
| L02 | ZAPDOS | `NewMauville_Inside` | (25, 28), elev 3 | 50 | Mind Badge only | Pending |
| L03 | MOLTRES | `MtChimney` | (20, 35), elev 3 | 50 | Mind Badge only | Pending |
| L04 | MEWTWO | `DesertUnderpass` | (10, 9), elev 0 | 70 | Hall of Fame | Pending |
| L05 | MEW | `PetalburgWoods` | (36, 35), elev 3 | 50 | Capture trails: CELEBI | Pending |
| L06 | RAIKOU | `Route118` | (42, 9), elev 3 | 50 | Mind Badge only | Pending |
| L07 | ENTEI | `FieryPath` | (23, 4), elev 3 | 50 | Mind Badge only | Pending |
| L08 | SUICUNE | `Route119` | (31, 106), elev 3 | 50 | Mind Badge only | Pending |
| L09 | LUGIA | `AbandonedShip_HiddenFloorRooms` | (34, 2), elev 3 | 70 | Hall of Fame; Capture trails: ARTICUNO, ZAPDOS, MOLTRES | Pending |
| L10 | HO OH | `MtPyre_Summit` | (22, 28), elev 3 | 70 | Hall of Fame; Capture trails: RAIKOU, ENTEI, SUICUNE | Pending |
| L11 | CELEBI | `Route120` | (22, 28), elev 3 | 50 | Mind Badge only | Pending |
| L12 | LATIAS | `Route123` | (79, 6), elev 3 | 50 | Mind Badge only | Pending |
| L13 | LATIOS | `Route115` | (27, 40), elev 3 | 50 | Mind Badge only | Pending |
| L14 | JIRACHI | `MeteorFalls_1F_1R` | (4, 38), elev 3 | 50 | Mind Badge only | Pending |
| L15 | DEOXYS | `MossdeepCity` | (19, 6), elev 3 | 70 | Hall of Fame | Pending |
| L16 | UXIE | `SafariZone_Northwest` | (20, 20), elev 3 | 50 | Mind Badge only | Pending |
| L17 | MESPRIT | `Route114` | (28, 38), elev 3 | 50 | Mind Badge only | Pending |
| L18 | AZELF | `Route120` | (17, 29), elev 3 | 50 | Mind Badge only | Pending |
| L19 | DIALGA | `SkyPillar_1F` | (11, 3), elev 3 | 70 | Hall of Fame; Capture trails: UXIE, MESPRIT, AZELF | Pending |
| L20 | PALKIA | `SeafloorCavern_Room9` | (4, 2), elev 3 | 70 | Hall of Fame; Capture trails: UXIE, MESPRIT, AZELF | Pending |
| L21 | HEATRAN | `FieryPath` | (26, 31), elev 3 | 70 | Hall of Fame | Pending |
| L22 | REGIGIGAS | `AncientTomb` | (8, 23), elev 3 | 70 | Hall of Fame; Regirock, Regice, Registeel together in party; no Eggs | Pending |
| L23 | GIRATINA | `MtPyre_6F` | (1, 3), elev 3 | 75 | Hall of Fame; Capture trails: DIALGA, PALKIA | Pending |
| L24 | CRESSELIA | `Route125` | (20, 20), elev 3 | 60 | Hall of Fame | Pending |
| L25 | PHIONE | `Route109` | (12, 2), elev 3 | 50 | Mind Badge only | Pending |
| L26 | MANAPHY | `Route105` | (13, 46), elev 3 | 50 | Mind Badge only | Pending |
| L27 | DARKRAI | `MtPyre_4F` | (1, 7), elev 3 | 70 | Hall of Fame | Pending |
| L28 | SHAYMIN | `Route117` | (53, 2), elev 3 | 50 | Mind Badge only | Pending |
| L29 | ARCEUS | `SkyPillar_Top` | (16, 11), elev 3 | 80 | Hall of Fame; Capture trails: GIRATINA, MEW, CELEBI, JIRACHI, MANAPHY, DARKRAI, SHAYMIN | Pending |

The six original Hoenn legendary events supplement these 29. Their original quest and capture mechanics are retained; do not infer their completion from the added-trail tests.

| ID | Original encounter | Ordinary route to verify | Status |
| --- | --- | --- | --- |
| O01 | Regirock | Complete Sealed Chamber unlock and Desert Ruins puzzle; capture and reload | Pending |
| O02 | Regice | Complete Sealed Chamber unlock and Island Cave puzzle; capture and reload | Pending |
| O03 | Registeel | Complete Sealed Chamber unlock and Ancient Tomb puzzle; capture and reload | Pending |
| O04 | Kyogre | Postgame Weather Institute report, reported sea route/Marine Cave; capture and reload | Pending |
| O05 | Groudon | Postgame Weather Institute report, reported land route/Terra Cave; capture and reload | Pending |
| O06 | Rayquaza | Preserve required weather-crisis story visit; later normal Sky Pillar summit capture and reload | Pending |

- [ ] Pending - Regigigas refuses with one Regi missing, stored in PC, or represented only by an Egg; accepts all three real Regis together.
- [ ] Pending - legendary trail flags remain distinct after multiple captures, PC operations and fresh reload.
- [ ] Pending - all 35 Gen 1-4 legendary/mythical base species appear in final acquisition ledger and retained collection.

## World Tournament

Exact attendant: `BattleFrontier_ReceptionGate` object **(2,11), elevation0**, Gentleman graphic, `CE_Tournament_EventScript`. Requires Hall of Fame/`FLAG_SYS_GAME_CLEAR`. Eight distinct opponents are drawn from32 regional leader teams, level75-77; player levels are open.

- [ ] Pending - access gate normally; pre-Champion refusal where naturally reachable; decline returns cleanly.
- [ ] Pending - accept entry; log every opponent and party for rounds1-8. Confirm no repeated opponent, correct teams/shininess, no unexpected level normalization.
- [ ] Pending - party heals before every round; PP/status/HP are restored as expected; between-round scripts do not expose unintended movement.
- [ ] Pending - win round8; winner dialogue and exactly one Gold Bottle Cap; return to field with controls.
- [ ] Pending - repeat a full tournament; distinct new draw may occur and exactly one additional reward is earned.
- [ ] Pending - lose in an early and a later round on labelled ordinary-save branches; whiteout/return works, no winner prize, new tournament starts at round1.
- [ ] Pending - from a naturally full Items pocket, complete round8: reward remains withheld; talk again while full retains prize; no duplicate or lost pending prize.
- [ ] Pending - save with withheld prize, fresh-process reload, free one whole item slot and collect exactly once.
- [ ] Pending - existing Gold Bottle Cap stack with one unit room accepts prize even if all pocket slots occupied; capped stack/full pocket keeps prize until room exists.
- [ ] Pending - save after collection, fresh-process reload and talk again: no second claim; new entry is offered after completed delivery.
- [ ] Pending - no second tournament begins while an earned prize remains pending.
- [ ] Pending - accumulate observed opponent IDs across repeated tournaments and verify all32 roster entries are reachable; mark any unobserved leader Pending, not failed merely because the draw is random.

## Red, Blue, Silver and Gold

Exact selector: `BattleFrontier_PokemonCenter_1F` object **(3,3), elevation3**, Cooltrainer M graphic, `CE_Superboss_EventScript`. Requires Hall of Fame. Dialogue advertises level95-97.

| ID | Opponent | Required normal-input checks | Status |
| --- | --- | --- | --- |
| B01 | Red | Select, correct shiny competitive team, win, safe field return, repeat after reload | Pending |
| B02 | Blue | Select, correct shiny competitive team, win, safe field return, repeat after reload | Pending |
| B03 | Silver | Select, correct shiny competitive team, win, safe field return, repeat after reload | Pending |
| B04 | Gold | Select, correct shiny competitive team, win, safe field return, repeat after reload | Pending |

- [ ] Pending - selector cancellation and pre-Champion refusal return safely; no forced challenge.
- [ ] Pending - ordinary loss/whiteout followed by replay; rewards/money/party remain consistent.
- [ ] Pending - competitive held items, moves, abilities and AI are observed in battle; dedicated portraits observed with correct palette, placement and clipping.

## Seven original Battle Frontier facilities

Reach facilities through normal postgame access. At each: normal registration/party eligibility, entry, battle or room flow, native win/loss/retirement handling, BP award, challenge records, save/continue behavior, and fresh battery reload of persistent progress. Respect each facility's own save/retirement rules; never quit during flash writes. Complete all offered offline formats relevant to the build. Link-only/multiplayer service exclusions are not ordinary offline passes.

| ID | Facility | Specific flow to exercise | Status |
| --- | --- | --- | --- |
| F01 | Battle Tower | Single and Double registration/sets; party restrictions, successive floors, win/loss, BP and records; multi partner route if offered offline | Pending |
| F02 | Battle Dome | Bracket/menu, opponent scouting, selection, successive rounds, final, retirement/loss and BP | Pending |
| F03 | Battle Palace | Nature-driven automatic move choices, battle flow, win/loss and records; confirm adviser battle nature interacts consistently | Pending |
| F04 | Battle Arena | Three-turn judging, judgement ties/results, forced party progression, win/loss and BP | Pending |
| F05 | Battle Factory | Rental selection, rental battle, swaps between rounds, set completion, retirement/loss and BP | Pending |
| F06 | Battle Pike | Three-path room choice, trainers/wild/status/healing events, final room, win/loss and BP | Pending |
| F07 | Battle Pyramid | Dark exploration, limited supplies/pickups, trainers/wild encounters, stairs/top, Bag restrictions and return | Pending |

- [ ] Pending - defeat each facility's Silver and Gold Frontier Brain under its normal streak conditions; verify symbols and Frontier Pass persistence after fresh reload.
- [ ] Pending - PC/party are restored after rental/facility restrictions; no permanent held-item, HP, move or species corruption.
- [ ] Pending - native Frontier records, BP exchanges and Hall of Fame coexist with expanded storage; save/reload after representative records change.

## Competitive adviser, inventory and menu checks

Confirmed service objects: Oldale Centre `OldaleTown_PokemonCenter_1F` (11,4), elevation3; Frontier Centre `BattleFrontier_PokemonCenter_1F` (10,4), elevation3. Verify other placed advisers as encountered; these two provide fixed reference locations.

- [ ] Pending - cancel at main menu, party chooser, nature/stat/EV menus and confirmation; no money, cap or Pokemon changes.
- [ ] Pending - reject Eggs; party-slot cancellation never selects another Pokemon; no menu state leaks across interactions.
- [ ] Pending - nature change with2999 money refuses; with3000 succeeds and consumes exactly3000; refusal/cancel consumes nothing. Obtain amounts through normal play.
- [ ] Pending - all25 battle natures selectable; stats change consistently, original breeding nature/PID-dependent appearance/gender remain; save/reload preserves identity and stats.
- [ ] Pending - Silver Cap sets only chosen IV to31 and consumes one cap; missing-cap refusal changes nothing.
- [ ] Pending - already-max selected IV consumes no Silver Cap; invalid/egg request consumes nothing.
- [ ] Pending - Gold Cap sets all six IVs to31, consumes one; already-max mon consumes none; missing-cap refusal unchanged.
- [ ] Pending - EV setter values0,4,127,128,251,252 selectable;127 must not act as B-button cancel;253 unavailable.
- [ ] Pending - set252 Attack +252 Speed +6 HP =510; adding another EV refuses atomically; lowering one stat permits redistribution.
- [ ] Pending - EV reset confirmation removes all six EVs; cancel preserves them; inspect recalculated stats and save/reload.
- [ ] Pending - nature/IV/EV work on injured and fainted Pokemon does not revive or corrupt HP unexpectedly; inspect current/max HP after recalculation.
- [ ] Pending - Bottle Cap/Gold Bottle Cap shop price, quantity, affordability, capacity, cancellation and resulting inventory checked through ordinary money/items.
- [ ] Pending - Summary visibly exposes expected IV/EV/battle-nature information; inspect selected Pokemon rather than assuming correct menu targeting.
- [ ] Pending - repeat long nature/EV/research/hints menus many times; controls, text bounds, scrolling and return remain stable.
- [ ] Pending - adviser service, item count, money and resulting Pokemon persist together after normal save/fresh reload; never claim transactional proof from one screen alone.

## Expanded storage and save integrity

Use naturally acquired Pokemon and labelled ordinary-save branches. Keep a per-slot ledger for stress cases.

- [ ] Pending - scroll BOX1 through BOX17 in both directions; correct names/wallpapers, count and wraparound; final slot BOX17 slot30 is accessible.
- [ ] Pending - deposit/withdraw/move/reorder across BOX1/BOX16/BOX17, party, held items and marking/summary menus; save/fresh reload verifies identity/moves/IVs/EVs/shiny state.
- [ ] Pending - all493 base species retained together, each identified by actual species/Dex number, with spare slots consistent with510 PC capacity.
- [ ] Pending - all510 PC slots filled through normal acquisition; with six-member party, a further capture fails safely rather than overwriting or losing a Pokemon.
- [ ] Pending - at full PC capacity, free a slot and confirm capture delivery to the expected box; no duplicate or lost Pokemon after reload.
- [ ] Pending - normal save alternation across several milestones retains party, BOX17 final slot, story/legend flags, pending tournament prize, BP/Frontier records and Hall of Fame.
- [ ] Pending - read existing native corrupted-slot recovery evidence separately; do not corrupt the canonical ordinary battery save or present native fault injection as ordinary gameplay.
- [ ] Pending - Egg deposit/withdraw/hatching and evolved/trained Pokemon survive box moves and reload; no cross-slot data contamination.
- [ ] Pending - if real hardware/flashcart testing is unavailable, retain hardware timing/audio/save-flash checks as Blocked; do not substitute emulator results.

## Dedicated portraits — implementation complete; gameplay review pending

The owner supplied the new atlas on 17 October 2026. All 18 dedicated assets and 34 trainer assignments are integrated at `d801d69748baa9570049a23864c1be74ea00e37c`. Existing picture IDs and the save format are preserved. Indexed PNG/source checks pass; native decode and palette results are recorded in the latest status report. Observe each portrait in its ordinary battle before marking its visual review Pass.

| Character | Dedicated front portrait |
| --- | --- |
| Falkner | `ce_falkner.png` |
| Bugsy | `ce_bugsy.png` |
| Whitney | `ce_whitney.png` |
| Morty | `ce_morty.png` |
| Chuck | `ce_chuck.png` |
| Jasmine | `ce_jasmine.png` |
| Pryce | `ce_pryce.png` |
| Clair | `ce_clair.png` |
| Roark | `ce_roark.png` |
| Gardenia | `ce_gardenia.png` |
| Maylene | `ce_maylene.png` |
| Crasher Wake | `ce_crasher_wake.png` |
| Fantina | `ce_fantina.png` |
| Byron | `ce_byron.png` |
| Candice | `ce_candice.png` |
| Volkner | `ce_volkner.png` |
| Gold | `ce_gold.png` |
| Silver | `ce_silver.png` |

Source mappings: `src/data/trainers.party`. Registry/resources: `include/constants/trainers.h` and `src/data/graphics/trainers.h`. Assets: `graphics/trainers/front_pics/`.

## Final gameplay sign-off

No final-playable certification until M00-M11, all individually listed visitor/starter/legend checks, all493 ledger/storage requirement, full tournament, four superbosses, seven facility flows and durable save checks have execution evidence. Separate confirmed feature defects from build/test limitations, unfinished artwork, upstream out-of-scope known failures and unavailable hardware checks. Preserve every remaining Pending/Blocked/Fail item in the master specification and permanent progress log.

Source references: `data/complete_edition_world.json`; `data/scripts/complete_edition_battles.inc`; `data/scripts/complete_edition_training.inc`; `data/scripts/complete_edition_research.inc`; `src/complete_edition{,_research,_legends,_tournament}.c`; the five exact service/attendant map files named above; `docs/COMPLETE_EDITION_FIELD_GUIDE.md`; `docs/COMPLETE_EDITION_LEGEND_TRAILS.md`. Static placement validation alone checks local ground/adjacency, not complete ordinary travel reachability.
## Local Windows emulator controls and baseline checkpoint

Runtime-verified on installed mGBA SDL0.10.5: ordinary Start/A/B/arrows, menu navigation and native F12 screenshots. Start with ROM basename, cwd set to the session directory, and forward-slash savegamePath/screenshotPath overrides. Keep a persistent host process owning the hidden child. SDL replaces its startup window; reacquire a unique current window only within that same verified PID. Never use savestate/rewind hotkeys.

Baseline save/reload PASS: original two-badge battery loads; ordinary in-game SAVE completes; graceful exit and fresh-process restart show Continue2:23/two badges and load Dewford Gym. Party: shiny male Marshtomp22,Mild,Torrent,55/82HP; Tackle/Rock Tomb/Mud-Slap/Water Gun. Read-only validation finds both complete flash slots valid, newest counter16; party and PC bytes unchanged from original. This verifies the baseline portion of M00; later progression and service-specific persistence remain pending.

Milestone battery CE_QA_20261017_Dewford_Baseline.sav SHA256 bc254160829475f279e7dc06c7bae9245b43cccdb1d29e2554826a4519dfc828. Original SHA256914e4b92f1e1df38009a010f44d3b062a64a6c4feef3cbebe3d28bcb47ed19c9 remains unchanged. Current working session06. New multi-button hold/pulse commands are still unverified in gameplay. Next: heal/check PC and Granite Cave/Flash/Steven's Letter. No story advancement beyond the recovered Dewford milestone is claimed.

## Executed Dewford and Granite Cave checks — 17 October 2026

PASS: Gym exit; town/Center transitions; nurse heal; PC opens; Box17-to-Box1 navigation; Sentret5 withdrawal; party menu with both Pokémon; ordinary save and fresh-process reload preserving withdrawal/HM05; Fisherman Ned victory; cave entry; hiker HM05 award. Shiny opponent Tentacool and wild Makuhita/Aron/Cleffa/Abra observed.

Pending: Flash teaching/use (current party incompatible), successful capture persistence, Steven Letter/exit/Slateport, and the remaining main-adventure/postgame/service/storage boundary checklist. A Cleffa fainting and Abra teleporting are ordinary attempt outcomes, not capture passes or feature defects.

Milestone CE_QA_20261017_GraniteCave_HM05.sav SHA2561295405399a5b6c9fa14fe236a09d0666b4400f06bb7285d999c44ad1360aae8,counter19,B1F(4,21). Both slots pass raw flash validation. Working session06 newer; inspect latest valid ordinary save before resuming.

Windows runner tools/complete_edition/mgba_session.py and mgba_buttons.py preserve existing save. Basic press/pulse/B+direction/native screenshots/quit have runtime observations; exact input duration is not a verified step count.0.22s walking presses are more reliable than0.15s;0.3s can take two tiles. Confirm scene transitions before issuing menu choices. Use in-game SAVE and read the battery for checkpoint position. Static source map binary reads require blob-hash validation.
