# Complete Edition — Alpha 2.2


**Development milestone, not a finished game.** Alpha 2.2 adds 29 legendary
world trails and linked prerequisites, fixes the Charge battle hang and Gen 4
Growth sunlight behavior, and includes the earlier stability corrections.
Alpha 2 / 2.1 battery saves remain compatible; back them up first.

The [stability report](COMPLETE_EDITION_STABILITY.md) records the exact audit
snapshots and current limits. Native and ordinary-input checks are distinct.
Full story, all seven Frontier facilities, all event interactions, portrait
replacement and hardware testing remain unfinished.

Current verification: **403 focused passes; 139 failing outcomes in the full native suite (5,253 passes / 5,905 results).** The focused profile also records four assumption skips, two known upstream failures and eleven TODO cases. These figures are not a finished-release certification.

## Implemented

- Generation 1–4 species enabled; later generations, regional forms and modern battle gimmick forms disabled. Gen 4 configuration defaults, types, learnsets and the physical/special split. Fairy typing is absent from the 493 base species.
- Universal shiny policy enforced at the stored shininess setter, including explicit non-shiny trainer templates. It preserves personality, gender and original trainer identity.
- Reusable original TMs. Plain trade evolutions become level-37 evolutions; held-item trade evolutions occur on the next level with the appropriate held item, which is consumed. Original location and other evolution alternatives remain.
- Training adviser in each of 16 Hoenn Pokémon Centres: battle-nature changes for 3,000; Silver Bottle Caps for one IV; Gold Bottle Caps for all IVs; free EV reset and exact 0–252 allocation, with the 510 total enforced. Caps cost 20,000/60,000. The nature service works like a Mint: the stat nature changes while breeding personality remains intact.
- 105 encounter tables now add other generations to Hoenn, starting with Pidgey, Sentret, Starly and Bidoof on Route 101. Twelve fixed, catchable starter sites replace the extra gift menu; badge gates, levels and locations are in the [field guide](COMPLETE_EDITION_FIELD_GUIDE.md). Failed captures remain retryable. The original opening starter choice and Castform gift remain. Birch's researcher sells evolution supplies and gives habitat advice.
- After earning the seventh Gym Badge (MIND BADGE from Tate and Liza), the researcher offers real, repeatable level-50 wild encounters for each of National Dex #1–493, including every legendary and mythical. These require ordinary capture and your own Poké Balls. The catalogue remains a repeatable fallback alongside the 29 new world trails and six original Hoenn legendary events.
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

Ubuntu 24.04, GCC ARM 13.2.1, binutils 2.42 and mGBA 0.10.2. Production
compilation passes the ARM object-integrity guard. Native emulator tests cover
all 493 shiny creations, trainer teams, Gen 4 mechanics, all 510 storage slots,
actual flash saves and damaged-sector fallback, research gates, starter flags,
and legendary prerequisites/completion flags. The Complete Edition group now
passes 34 tests. The physical/special split remains enabled; no move or ability
has been removed.

Targeted reruns pass all 75 trainer-slide cases, 21 Future Sight cases, 9
experience cases, and 13 Transform cases, alongside the other regression groups
recorded in the stability report. Upstream TODO/KNOWN_FAILING outcomes remain
explicit and are not passes.

The first complete continued audit had 5,212 passes and 170 failing outcomes
across 5,897 results, with no TIMEOUT or ERROR outcomes. Its exact
backlog is retained in `qa/2026-10-15-before-final-fixture-fixes.json`. That
snapshot precedes the latest Growth and fixture fixes; a new broad run is
required to measure their aggregate result. It cannot be called release-clean.

Ordinary button-input QA includes the opening story, first rival victory,
Pokédex handover, running shoes, nature/EV service transactions, BOX17, healing,
catching a shiny Sentret on Route 101, and Calvin/Rick trainer victories.
A fresh emulator process loaded the ordinary battery save with Pokédex
progress intact. Legendary hints and the pre-badge catalogue refusal work in
the production ROM. This is early-game testing, not a complete story or
Frontier playthrough.

All 84 added placements pass floor, stable-terrain, elevation, adjacent-access,
overlap and map-template checks. Map checks do not replace travel testing.

## Build and patch

- ROM SHA-256: `bb70e00f7e17c5e99018e5e8d2d4c4672640accb864f75a121d625bfe32d8fb0`.
- Linked ROM region: 16,557,076 bytes; padded file: 16 MiB, within the 32 MiB GBA limit.
- EWRAM: 235,496/262,144 bytes. IWRAM: 28,364/32,768 bytes.
- Patch input: clean Emerald US/EU revision 0, 16 MiB; SHA-1 `f3ae088181bf583e55daf962a92bb46f4f1d07b7`; CRC32 `1f1c08fb`.
- BPS creation validates the input and an exact patch-application round trip against the compiled target.
- No retail ROM or compiled ROM is committed to the repository.

## Required before a final release

- Start a new game if coming from Alpha 1, original Emerald or an incompatible experimental build. Alpha 2 / 2.1 battery saves remain supported; keep a backup.
- The 510-slot storage expansion passes actual flash tests; its UI and all facility-specific save paths still need normal-play QA.
- Play through all story gates, Champion defeat/Hall of Fame, postgame unlocks and save/reload. Size checks are not a save/reload playthrough.
- Exercise all new menus, captures, loss/whiteout paths, full-party/full-PC gifts, and an entire tournament in normal play.
- Resolve or explicitly classify the full-suite failures, then run the agreed regression profile cleanly.
- Test all seven Battle Frontier facilities, timing/audio and a flashcart on real GBA hardware. Hardware compatibility is a design constraint, not yet a hardware-tested claim.
- Replace temporary existing portraits used for Johto/Sinnoh leaders and Gold/Silver; improve event presentation and balance the teams through playtesting.
- Complete travel, interaction and capture/save/reload QA for all 29 new legendary trails. The catalogue continues to unlock after the seventh badge.

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
