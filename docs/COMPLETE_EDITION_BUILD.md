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
