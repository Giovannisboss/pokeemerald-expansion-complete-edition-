# Complete Edition — Alpha 2.1

This is a boot-tested development milestone, not a completed or release-certified game.

## Implemented

- Generation 1–4 species enabled; later generations, regional forms and modern battle gimmick forms disabled. Gen 4 configuration defaults, types, learnsets and the physical/special split. Fairy typing is absent from the 493 base species.
- Universal shiny policy enforced at the stored shininess setter, including explicit non-shiny trainer templates. It preserves personality, gender and original trainer identity.
- Reusable original TMs. Plain trade evolutions become level-37 evolutions; held-item trade evolutions occur on the next level with the appropriate held item, which is consumed. Original location and other evolution alternatives remain.
- Training adviser in each of 16 Hoenn Pokémon Centres: battle-nature changes for 3,000; Silver Bottle Caps for one IV; Gold Bottle Caps for all IVs; free EV reset and exact 0–252 allocation, with the 510 total enforced. Caps cost 20,000/60,000. The nature service works like a Mint: the stat nature changes while breeding personality remains intact.
- 105 encounter tables now add other generations to Hoenn, starting with Pidgey, Sentret, Starly and Bidoof on Route 101. Twelve fixed, catchable starter sites replace the extra gift menu; badge gates, levels and locations are in the [field guide](COMPLETE_EDITION_FIELD_GUIDE.md). Failed captures remain retryable. The original opening starter choice and Castform gift remain. Birch's researcher sells evolution supplies and gives habitat advice.
- After earning the seventh Gym Badge (MIND BADGE from Tate and Liza), the researcher offers real, repeatable level-50 wild encounters for each of National Dex #1–493, including every legendary and mythical. These require ordinary capture and your own Poké Balls. This catalogue is an initial availability implementation; it is not a set of bespoke legendary quests or natural route placements.
- Steven is the Champion with a separate level-58–60 team. Champion-room and Hall of Fame sprites/dialogue name updated; original story movement scripts and Meteor Falls Steven encounter retained.
- Modest trainer level increase: levels 10–70 gain approximately 5%, at least one level. Tutorials and levels below 10 are unchanged.
- 24 optional visiting leaders now stand individually in appropriate locations around Hoenn, with original badge gates and three-Pokémon teams, levels 18–54. The Centre visitor desks are removed. Full locations are in the field guide.
- World Tournament desk at the Battle Frontier Reception Gate. Eight single battles, random opponents without repeats from all 32 regional leaders, full party healing between rounds, level-75–77 opponents, Gold Bottle Cap reward. This is open-level, not level-normalised or an exact recreation of the official PWT rules.
- Repeatable Red, Blue, Silver and Gold challenges at the Battle Frontier Pokémon Centre. Six Pokémon each, levels 95–97, perfect IVs, legal EV totals, held items and explicit Gen 4 movesets.
- New Press Start screen: shiny-Rayquaza artwork over Hoenn, native Complete Edition lettering, blinking prompt and looping title music. Mode 0, 600 8bpp tiles; text has separate 4bpp VRAM and palette space. Original intro and title button combinations retained. Developer menus/quickstart remain disabled. Artwork provenance and generation prompt accompany the committed indexed PNG.

## Locations and saves

See the [Alpha 2.1 field guide](COMPLETE_EDITION_FIELD_GUIDE.md) for all 12 starter encounters, all 24 leader locations and early wild examples. `data/complete_edition_world.json` records exact coordinates, badge gates and encounter levels.

The PC now has 17 boxes (510 slots). Standard 128 KiB flash and both alternating save snapshots are retained. Alpha 2.1 retains Alpha 2's save format and accepts its battery saves. The format rejects incompatible Alpha 1/original saves. Old distribution/e-Reader/chat/multiplayer-record buffers were reclaimed; story, Match Call, Trainer Hill, Hall of Fame and Battle Frontier save data remain. See the build guide for the storage layout.

## Alpha 2.1 changes

Both the script menu and native encounter factory now check `FLAG_BADGE07_GET`. A native test covers zero through eight badges without Champion status; all 493 research creations also run with the Champion flag cleared. Capture tests now select the Quick Ball generation explicitly, and its implementation reads the runtime configuration consistently. A Gen 4/5 odds test covers both multipliers. The ally-redirect Lightning Rod test now explicitly requests the Gen 5 immunity/stat-boost behavior that its assertions require. These corrections preserve the production Gen 4 rules.

## Verification

Ubuntu 24.04, GCC ARM 13.2.1, binutils 2.42. Baseline build and new-game menu/Birch introduction verified in mGBA 0.10.2. The Alpha 2 artwork, blinking Start prompt and transition to the ordinary new-game menu were visually inspected at 240×160 after the original intro.

| Focused mGBA test group | Passed | Inapplicable assumptions |
| --- | ---: | ---: |
| Complete Edition | 17 | 0 |
| Pokémon | 25 | 3 |
| Daycare/breeding | 38 | 0 |
| Save layout | 4 | 0 |
| Trainer control | 20 | 1 |
| Total | 104 | 4 |

Feature tests include all 493 species with three OT-ID methods, 493 actual research-mon creations, all 61 custom production trainer parties, exact cap consumption, invalid/Egg handling, EV limits, all 253 EV menu values, catalogue cancel-ID collisions and a complete 32-opponent tournament draw without repeats. A compiled wild-table/evolution check covers all 458 ordinary species via wild encounters, the twelve starter sites and the original Castform gift.

Actual emulated flash tests restore a trained party and the final PC slot; fill all 510 slots and preserve complete storage metadata; deliberately corrupt footer data or a sector ID and recover the previous snapshot; and preserve PC consistency during partial Frontier/link saves.

All 55 added NPC placements pass static checks for passable floor, compatible elevation, adjacent access, overlapping objects and the 64 map-template limit. The engine still limits simultaneously active objects to 16; normal spatial activation applies. Starter scripts are checked to set their hide flag only after `B_OUTCOME_CAUGHT`. Complete travel and interaction QA remains necessary.

The Alpha 2.1 full-suite rerun ended before producing final totals. It recorded 5182 completed test results; the partial log is included in the patch package. The targeted capture and ally Lightning Rod corrections pass, resolving two previously failing cases in focused runs. A complete new broad-profile failure count is not yet verified. Previous Alpha 2 full upstream run: **5,163 passed / 5,899 total; 218 failed, 18 known failing, 70 assumption failures, 421 TODO and 9 expected failures**. The 218 failing test names are identical to Alpha 1's recorded full-profile failures; the three extra passing tests reflect the replacement of the gift test with new storage and availability checks. The full suite still exits with failure, so a final-release claim would be premature.

The new flash-save tests initially left the test runner's Timer 2 watchdog replaced by the flash handler. Their fixture now restores the interrupt handler, timer registers and interrupt-enable mask before returning. The corrected full run completed; this fixture fix does not change the production ROM.

Several full-suite failures are configuration mismatches: for example newer-generation damage/experience expectations and Future Sight typing. Not all failures have been triaged; they must not all be dismissed as harmless. The focused CI workflow is explicit about its scope; it does not imply the full upstream suite passes.

## Build and patch

- ROM SHA-256: `6140e28c56f6e5ab954ae94df8a468cb266c21d49ee022a10230c654a4498f57`.
- ROM before padding: 16,544,892 bytes; padded file: 16 MiB, within the 32 MiB GBA limit.
- EWRAM: 235,496/262,144 bytes. IWRAM: 28,364/32,768 bytes.
- Patch input: clean Emerald US/EU revision 0, 16 MiB; SHA-1 `f3ae088181bf583e55daf962a92bb46f4f1d07b7`; CRC32 `1f1c08fb`.
- BPS creation validates the input and an exact patch-application round trip against the compiled target.
- No retail ROM or compiled ROM is committed to the repository.

## Required before a final release

- Start a **new game**. Alpha 1, original Emerald and earlier experimental saves are incompatible with the new storage/save format.
- The 510-slot storage expansion passes actual flash tests; its UI and all facility-specific save paths still need normal-play QA.
- Play through all story gates, Champion defeat/Hall of Fame, postgame unlocks and save/reload. Size checks are not a save/reload playthrough.
- Exercise all new menus, captures, loss/whiteout paths, full-party/full-PC gifts, and an entire tournament in normal play.
- Resolve or explicitly classify the full-suite failures, then run the agreed regression profile cleanly.
- Test all seven Battle Frontier facilities, timing/audio and a flashcart on real GBA hardware. Hardware compatibility is a design constraint, not yet a hardware-tested claim.
- Replace temporary existing portraits used for Johto/Sinnoh leaders and Gold/Silver; improve event presentation and balance the teams through playtesting.
- Add bespoke world events/quests for legends still using the research catalogue. Natural ordinary habitats now exist; the catalogue unlocks after the seventh badge.
