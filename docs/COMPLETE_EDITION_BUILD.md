# Complete Edition development

Work on `complete-edition-development`. No retail ROM is needed to compile.

## Current commands and verification — 17 October 2026

The latest full native baseline is source`a18692567ed17b4a1cef13fec1cf253167c72ae9`, run39030540953:51/51 focused Complete Edition outcomes pass; full suite5,424 PASS/5,922 total/zero unexpected failures. Five known failures,63 assumption skips,421 TODOs,seven expected failures and two deliberate expected crashes remain explicit. See the current status page for evidence and remaining release gates. The historical Alpha1/Alpha2 sections below describe their original milestones.

```sh
./tools/complete_edition/build.sh
./tools/complete_edition/test.sh --ce-only
./tools/complete_edition/test.sh --full
python3 -m unittest discover -s tools/complete_edition -p 'test_bps.py' -v
python3 -m unittest discover -s tools/complete_edition -p 'test_package_release.py' -v
```

Use sequential native test runs because the host runner shares temporary filenames. Current development builds retain the Alpha2 save layout: back up existing Alpha2 battery saves before upgrading; Alpha1/original Emerald saves are incompatible. New native test coverage does not itself require starting over.

### Patch-only development package

Keep both ROMs outside the published package. With your own correct clean input and the compiled target:

```sh
python3 tools/complete_edition/package_release.py /private/clean-emerald.gba pokeemerald.gba /private/CompleteEdition-development
```

The output must be a new directory. It contains only`CompleteEdition.bps`,`release.json`,`README.txt` and`SHA256SUMS`. The packager checks the exact source SHA1,nonempty/maximum target size,BPS CRCs and an exact round trip before publishing the staged output. It never copies either ROM into the package,never modifies the inputs,and refuses an existing output path. Check the patched ROM against`target_sha256` in the manifest. This verifies patch integrity,not story/gameplay completion.

Dedicated release-tool CI runs these synthetic tests without a retail ROM. Packaging-only files and documentation do not trigger redundant native builds; game/engine/test changes still run the native workflow. Both workflows retain manual dispatch. No full-ROM artifact is published by the current configuration.

Current ordinary QA uses normal controls and battery saves with fresh-process reloads. Do not use the historical controller's`save`/`load` savestate commands for progression,recovery or gameplay evidence. Ordinary story/postgame verification remains deferred; dedicated portraits and final release checks remain open.

## Ubuntu 24.04 / Codespaces

The `.devcontainer` installs the build dependencies automatically. For an existing Ubuntu system:

```sh
sudo apt-get update
sudo apt-get install -y --no-install-recommends build-essential git binutils-arm-none-eabi gcc-arm-none-eabi libnewlib-arm-none-eabi libpng-dev python3
./tools/complete_edition/build.sh
```

The output is `pokeemerald.gba`. Build logs and SHA-256 hashes are saved in `build/complete-edition-logs/`. Set `JOBS` to adjust parallelism (default 4).

## Emulator tests

```sh
make -j4 KEEP_TEMPS=1 check TESTS="test/pokemon.c"
make -j4 KEEP_TEMPS=1 check
```

The repository includes the upstream headless mGBA runner. These tests execute ARM game code in the emulator. They do not replace manual adventure, save/load, sound, timing and real-hardware checks. A successful compile alone is not proof of a playable adventure.

Keep generated ROMs, saves and any original retail dump out of Git. A distributable patch must identify and validate the exact clean input ROM; do not publish full ROMs.

## Verified baseline (2026-10-15)

Source: `8caa22de47f5820d2bbfbeb242bb94358ec0dafc`. GCC 13.2.1, binutils 2.42, Ubuntu 24.04. Initial streaming compilation produced four empty objects; rebuilding with `KEEP_TEMPS=1` resolved the link failure. The build script always uses that mode.

Baseline ROM SHA-256: `3a1d109bc56cac680e7fe12c2a7661cdf999eb76912ece5042d5059f0a29f575`. ROM 26,750,724 bytes before padding; EWRAM 226,416 bytes; IWRAM 28,376 bytes. mGBA 0.10.2 rendered the new-game menu at 1,000 frames and Birch introduction at 1,800 frames using real button inputs. Story completion, save/load and hardware have not yet been verified.

To run the visual smoke harness (optional host dependency `libmgba-dev`):

```sh
gcc -O2 -Wall -Wextra tools/complete_edition/smoke.c -lmgba -o /tmp/ce-smoke
timeout 40 /tmp/ce-smoke pokeemerald.gba /tmp/newgame.ppm 1800 9
```

## Historical Alpha 1

Run `./tools/complete_edition/test.sh` for the focused production-profile checks and map validation. `./tools/complete_edition/test.sh --full` runs the full upstream suite; at that historical milestone it had unresolved failures. Current full-suite evidence is recorded above. See `COMPLETE_EDITION_STATUS.md` for evidence and limits.

Quickstart and all developer menus are disabled. A **new save is required**: species settings and trainer-flag allocation deliberately differ from upstream and earlier experimental builds.

Create a patch using your own clean US/EU revision-0 ROM (outside this checkout):

```sh
python3 tools/complete_edition/bps.py /private/clean-emerald.gba pokeemerald.gba /private/complete-edition.bps
```

The tool verifies the input SHA-1, the GBA size limit, and an apply-to-clean-ROM round trip with CRC32 checks before writing the patch. Neither input nor output ROM belongs in Git.

## Alpha 2 save format

Use a new game: Alpha 1 and original Emerald saves are deliberately rejected by the new `0xCE000002` sector signature. Keep earlier ROM/save pairs under their original names. Standard 128 KiB flash, alternating 14-sector snapshots and sectors 28–31 (Hall of Fame, Trainer Hill and recorded battles) remain.

Seventeen boxes provide 510 normal slots. `PokemonStorage` is 41,276 bytes: 35,712 bytes remain in its nine sectors, and the 5,564-byte tail is copied losslessly into reserved SaveBlock1/2/3 buffers (2,584/1,424/1,556 bytes). SaveBlock sizes are 15,872 / 3,968 / 1,560 bytes. Legacy distribution/chat/multiplayer-record buffers and one unused post-Gen-4 fusion slot were reclaimed. Persistent Dex bitsets reserve the same extent in production and the all-species test runner.

Full saves pack the PC tail; partial Frontier/link saves preserve the previous full PC snapshot. Footer chunks are now checksum-protected, and invalid sector IDs cannot index the layout table. `test/complete_edition_flash.c` exercises actual emulated flash writes, all 510 slots, metadata, corrupted newest-slot fallback and partial-save consistency.

The title artwork is a committed indexed PNG with normal automatic asset conversion. Building needs no image-generation service. Artwork provenance and prompt are in `graphics/title_screen/COMPLETE_EDITION_ART.md`.

To export a searchable ordinary-wild encounter list:

```sh
python3 tools/complete_edition/export_encounters.py /path/outside/repo/Wild_Encounters.csv
```

Flash tests restore Timer 2's test-watchdog handler and timer registers after exercising the production flash routines; otherwise later full-suite tests can lose their timeout interrupt.

## Button-input playthrough controller

The optional host controller runs the unmodified production ROM, accepts buttons,
and captures images/checkpoints. It deliberately exposes no memory-write command.
Read-only memory inspection can identify the current map and coordinates.
Emulator checkpoints are private QA files, never a replacement for battery-save tests.

```sh
gcc -O2 -Wall -Wextra tools/complete_edition/play.c -lmgba -o /tmp/ce-play
/tmp/ce-play /private/qa.gba
```

Commands: `run MASK FRAMES` holds buttons; `pulse MASK FRAMES` presses for eight
frames every thirty frames; `shot /absolute/path.ppm` captures the screen;
`save /absolute/path.state` and `load /absolute/path.state` handle checkpoints;
`read HEX_ADDRESS BYTE_COUNT` reads at most 256 bytes; `position HEX_POINTER`
dereferences the ELF symbol address of `gSaveBlock1Ptr` and reports map/coordinates;
`quit` exits. An optional second argument records commands with frame numbers. Key masks:
A=1, B=2, Select=4, Start=8, Right=16, Left=32, Up=64, Down=128, R=256, L=512.
Each run is bounded to 36,000 frames. Use short single presses around dialogue
and menus: repeatedly pressing A can close and reopen a sign.

`walk MASK FRAMES BATTLE_FLAG [FIELD_LOCK]` accepts the optional matching-ROM
address of `sLockFieldControls`. With it, walking stops as soon as a field script
locks controls, including trainer introductions before the battle flag is set.
It reports `(field script)` so the caller can inspect the screen and position
before continuing. Both guarded and legacy formats were verified in ordinary play.
Map routes still need live position checks: dynamic NPCs can block a static path.

For read-only save inspection, derive structure offsets from the current headers
with the production `-mabi=apcs-gnu` ABI. Historical offset comments in `global.h`
can differ from this configured layout. On Alpha 2.5, the compiled SaveBlock1
flags offset is `0x123C`, and `SYSTEM_FLAGS` is `0x8A0`.


### Button-only battle QA helper

Build the host controller with `gcc -O2 -Wall -Wextra tools/complete_edition/play.c -lmgba -o /tmp/ce-play`.
Its `fight` command accepts packed move slots (left slot in bits 0–1, right
slot in bits 2–3), a bounded frame budget and read-only addresses for the battle
flag, controller array, action/move input handlers, cursor arrays, callback2
address and expected battle callback. An optional final target-input-handler address
confirms the game's default enemy target in doubles; choose important targets manually. For example, slot value 3 chooses left
move 3 and right move 0. The callback guard stops automation when another menu
or evolution callback takes control. Obtain symbols from the matching production ELF using
`arm-none-eabi-nm`; do not reuse addresses from another ROM revision. The helper
selects Fight and the requested move using normal buttons, advances messages and
declines optional switches. It does not refill PP, heal, edit memory or handle
all fainting/party/learning states. Review screenshots and journal entries when
it reaches the frame limit. Continue normal saves and fresh-process reload QA;
internal emulator states do not prove battery-save compatibility.


The optional `plan_walk.py MAP START_X START_Y GOAL_X GOAL_Y` helper produces
conservative foot routes from static map tiles. It respects walking elevation,
NPC origins and bridges, and prefers paths with less grass. Extra observed NPC
positions can be supplied with `--blocked X,Y`. Moving NPCs, trainer sight lines,
encounters and special terrain still require live position checks after each
segment; the helper never operates or changes game memory.


## Alpha 2.5 verification

The frozen engine/test tree `94e05b7e637809f718b068a50d33e73d657b7713`
passed the complete native audit: 5,397 PASS, no unexpected failure outcomes,
63 assumption skips, 16 known failures, 421 TODOs and nine expected outcomes.
Run native `make check` jobs sequentially: the headless runner uses shared host
temporary names even when ELF output names differ. Production compilation may
run independently. See the Alpha 2.5 QA JSON for exact scope and remaining gaps.

The subsequent field-resource fix is tree
`8942ab795b3c900133782efe904ddeaec7da1e3d`. It enables nine placed NPC graphics
that were accidentally gated behind IS_FRLG. All 61 placed graphics IDs pass
native validation. Final outcome-coverage details (including the incomplete
broad recheck and its focused completion) are in the final-coverage QA JSON.

## Alpha 2.5.1: no Dynamax gameplay

`B_DYNAMAX_ENABLED` defaults to `FALSE`. Both eligibility and direct activation
are guarded. Production compiles these to false/no-op; no save-layout changes
are made. The general battle-test harness enables the legacy backend solely
for upstream mechanics coverage; the new Complete Edition regression explicitly
disables it and tests both sides, Gigantamax metadata and direct activation.
The isolated final ROM passes 40 focused native tests and prior-save field reload.
Other experimental battle changes were excluded from this patch.
