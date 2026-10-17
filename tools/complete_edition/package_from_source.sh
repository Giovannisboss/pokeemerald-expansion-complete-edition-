#!/usr/bin/env bash
# Rebuild the byte-identical clean reference privately; distribute only the patch.
set -euo pipefail
root="$(pwd)"
work="$(mktemp -d "${RUNNER_TEMP:-/tmp}/ce-reference.XXXXXX")"
git init -q "$work/pokeemerald"
git -C "$work/pokeemerald" remote add origin https://github.com/pret/pokeemerald.git
git -C "$work/pokeemerald" fetch --depth 1 origin 731ad5bfd6e6f265508d0efcca0ba42f9dcf5881
git -C "$work/pokeemerald" checkout --detach FETCH_HEAD
git init -q "$work/agbcc"
git -C "$work/agbcc" remote add origin https://github.com/pret/agbcc.git
git -C "$work/agbcc" fetch --depth 1 origin da598c1d918402c42c0c0d7128ba14567f3175e9
git -C "$work/agbcc" checkout --detach FETCH_HEAD
(cd "$work/agbcc" && ./build.sh && ./install.sh "$work/pokeemerald")
make -C "$work/pokeemerald" -j4
echo "f3ae088181bf583e55daf962a92bb46f4f1d07b7  $work/pokeemerald/pokeemerald.gba" | sha1sum --check -
python3 "$root/tools/complete_edition/package_release.py" "$work/pokeemerald/pokeemerald.gba" "$root/pokeemerald.gba" "$root/build/complete-edition-release"
