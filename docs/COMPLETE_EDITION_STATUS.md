# Complete Edition — Alpha 1

This is a boot-tested development milestone, not a completed or release-certified game.

## Implemented

- Generation 1–4 species enabled; later generations, regional forms and modern battle gimmick forms disabled. Gen 4 configuration defaults, types, learnsets and the physical/special split. Fairy typing is absent from the 493 base species.
- Universal shiny policy enforced at the stored shininess setter, including explicit non-shiny trainer templates. It preserves personality, gender and original trainer identity.
- Reusable original TMs. Plain trade evolutions become level-37 evolutions; held-item trade evolutions occur on the next level with the appropriate held item, which is consumed. Original location and other evolution alternatives remain.
- Training adviser in each of 16 Hoenn Pokémon Centres: battle-nature changes for 3,000; Silver Bottle Caps for one IV; Gold Bottle Caps for all IVs; free EV reset and exact 0–252 allocation, with the 510 total enforced. Caps cost 20,000/60,000. The nature service works like a Mint: the stat nature changes while breeding personality remains intact.
- Birch's lab researcher offers one of each of the 12 starters at level 5 after the first badge, plus evolution supplies.
- After becoming Champion, the researcher offers real, repeatable level-50 wild encounters for each of National Dex #1–493, including every legendary and mythical. These require ordinary capture and your own Poké Balls. This catalogue is an initial availability implementation; it is not a set of bespoke legendary quests or natural route placements.
- Steven is the Champion with a separate level-58–60 team. Champion-room and Hall of Fame sprites/dialogue name updated; original story movement scripts and Meteor Falls Steven encounter retained.
- Modest trainer level increase: levels 10–70 gain approximately 5%, at least one level. Tutorials and levels below 10 are unchanged.
- 24 optional visiting leaders: Kanto, Johto and Sinnoh groups of three at eight Pokémon Centre visitor desks, gated by badge number. Three Pokémon per visitor, levels 18–54.
- World Tournament desk at the Battle Frontier Reception Gate. Eight single battles, random opponents without repeats from all 32 regional leaders, full party healing between rounds, level-75–77 opponents, Gold Bottle Cap reward. This is open-level, not level-normalised or an exact recreation of the official PWT rules.
- Repeatable Red, Blue, Silver and Gold challenges at the Battle Frontier Pokémon Centre. Six Pokémon each, levels 95–97, perfect IVs, legal EV totals, held items and explicit Gen 4 movesets.
- Native GBA Complete Edition title banner, using four sprites and 1 KiB of graphics. Original Emerald logo, title animation and copyright retained. Developer menus and title quickstart disabled.

## Where to find visiting leaders

| Centre | Required badge | Kanto | Johto | Sinnoh |
| --- | --- | --- | --- | --- |
| Rustboro | 1 | Brock | Falkner | Roark |
| Dewford | 2 | Misty | Bugsy | Gardenia |
| Mauville | 3 | Lt. Surge | Whitney | Maylene |
| Lavaridge | 4 | Erika | Morty | Wake |
| Fortree | 5 | Koga | Chuck | Fantina |
| Lilycove | 6 | Sabrina | Jasmine | Byron |
| Mossdeep | 7 | Blaine | Pryce | Candice |
| Sootopolis | 8 | Giovanni | Clair | Volkner |

The Hoenn tournament entrants are Roxanne, Brawly, Wattson, Flannery, Norman, Winona, Tate/Liza and Juan. Wallace retains his original Sootopolis story role.

## Verification

Ubuntu 24.04, GCC ARM 13.2.1, binutils 2.42. Baseline build and new-game menu/Birch introduction verified in mGBA 0.10.2. The final title banner was visually inspected at 240×160.

| Focused mGBA test group | Passed | Inapplicable assumptions |
| --- | ---: | ---: |
| Complete Edition | 13 | 0 |
| Pokémon | 25 | 3 |
| Daycare/breeding | 38 | 0 |
| Save layout | 4 | 0 |
| Trainer control | 20 | 1 |
| Total | 100 | 4 |

Feature tests include all 493 species with three OT-ID methods, 493 actual research-mon creations, all 61 custom production trainer parties, all 12 starter gifts and duplicate prevention, exact cap consumption, invalid/Egg handling, EV limits, all 253 EV menu values, catalogue cancel-ID collisions and a complete 32-opponent tournament draw without repeats. The production trainer data is explicitly included in the test because upstream normally replaces it with dummy trainers.

All 27 added NPC placements pass static checks for passable floor, compatible elevation, adjacent access, overlapping objects and map object limits. Full travel and interaction QA remains necessary.

Final full upstream run: **5,160 passed / 5,896 total; 218 failed, 18 known failing, 70 assumption failures, 421 TODO and 9 expected failures**. The previous milestone had 220 failures; the intended shiny-template expectation and the intentional new save layout were updated, accounting for the two resolved failures. The full suite still exits with failure. A final-release claim would be premature.

Several full-suite failures are configuration mismatches: for example newer-generation damage/experience expectations and Future Sight typing. Not all failures have been triaged; they must not all be dismissed as harmless. The focused CI workflow is explicit about its scope; it does not imply the full upstream suite passes.

## Build and patch

- ROM SHA-256: `a431f8bcdcc39713c8346688ad235c764b5fb4d6dcb7b3a43eeff42ab75e9089`.
- ROM before padding: 16,517,772 bytes; padded file: 16 MiB, within the 32 MiB GBA limit.
- EWRAM: 226,296/262,144 bytes. IWRAM: 28,376/32,768 bytes.
- Patch input: clean Emerald US/EU revision 0, 16 MiB; SHA-1 `f3ae088181bf583e55daf962a92bb46f4f1d07b7`; CRC32 `1f1c08fb`.
- BPS creation validates the input and an exact patch-application round trip against the compiled target.
- No retail ROM or compiled ROM is committed to the repository.

## Required before a final release

- Start a **new game**. Original Emerald saves and earlier experimental Complete Edition saves are not compatible with the changed species/trainer flag layout.
- PC capacity remains 14 boxes (420 slots) plus the party. All 493 can be caught and registered in one save, but a simultaneous living collection needs a storage/save-layout expansion.
- Play through all story gates, Champion defeat/Hall of Fame, postgame unlocks and save/reload. Size checks are not a save/reload playthrough.
- Exercise all new menus, captures, loss/whiteout paths, full-party/full-PC gifts, and an entire tournament in normal play.
- Resolve or explicitly classify the full-suite failures, then run the agreed regression profile cleanly.
- Test all seven Battle Frontier facilities, timing/audio and a flashcart on real GBA hardware. Hardware compatibility is a design constraint, not yet a hardware-tested claim.
- Replace temporary existing portraits used for Johto/Sinnoh leaders and Gold/Silver; improve event presentation and balance the teams through playtesting.
- Replace the catch-all research catalogue with curated natural habitats and legendary quests if desired. The alpha intentionally uses the catalogue to guarantee single-save roster access first.
