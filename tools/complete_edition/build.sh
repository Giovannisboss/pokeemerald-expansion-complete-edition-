#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/../.."
for tool in arm-none-eabi-gcc arm-none-eabi-as arm-none-eabi-ld make gcc g++ python3; do
    command -v "$tool" >/dev/null || { echo "Missing dependency: $tool. See docs/COMPLETE_EDITION_BUILD.md" >&2; exit 1; }
done
mkdir -p build/complete-edition-logs
jobs="${JOBS:-4}"
arm-none-eabi-gcc --version | head -1
make -j"$jobs" -O KEEP_TEMPS=1 all 2>&1 | tee build/complete-edition-logs/build.log
sha256sum pokeemerald.gba | tee build/complete-edition-logs/SHA256SUMS
