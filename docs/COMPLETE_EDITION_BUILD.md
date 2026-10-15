# Complete Edition development

Work on `complete-edition-development`. No retail ROM is needed to compile.

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
make -j4 -O KEEP_TEMPS=1 check TESTS="test/pokemon.c"
make -j4 -O KEEP_TEMPS=1 check
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

## Alpha 1

Run `./tools/complete_edition/test.sh` for the focused production-profile checks and map validation. `./tools/complete_edition/test.sh --full` runs the full upstream suite; it currently has unresolved failures under Gen 4 defaults and is not a release gate that passes. See `COMPLETE_EDITION_STATUS.md` for evidence and limits.

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
