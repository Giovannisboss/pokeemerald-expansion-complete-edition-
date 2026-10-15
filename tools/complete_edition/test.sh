#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/../.."
mkdir -p build/complete-edition-logs
python3 tools/complete_edition/validate.py | tee build/complete-edition-logs/placements.log
filters=("Complete Edition" "test/pokemon.c" "test/daycare.c" "test/save.c" "test/battle/trainer_control.c")
if [[ "${1:-}" == "--full" ]]; then
    filters=("")
fi
index=0
for filter in "${filters[@]}"; do
    make -j"${JOBS:-4}" -O KEEP_TEMPS=1 check TESTS="$filter" 2>&1 | tee "build/complete-edition-logs/tests-$index.log"
    index=$((index+1))
done
