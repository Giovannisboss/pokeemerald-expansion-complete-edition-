#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/../.."
mkdir -p build/complete-edition-logs
python3 tools/complete_edition/validate.py | tee build/complete-edition-logs/placements.log
filters=("Complete Edition" "test/pokemon.c" "test/daycare.c" "test/save.c" "test/battle/trainer_control.c" "test/battle/capture.c" "test/battle/wild_battle.c" "test/battle/ability/lightning_rod.c" "test/battle/ability/storm_drain.c" "test/battle/ability/filter.c" "test/battle/ability/iron_fist.c" "test/battle/move_effect/charge.c")
if [[ "${1:-}" == "--full" ]]; then
    filters=("")
fi
index=0
failed=0
for filter in "${filters[@]}"; do
    log="build/complete-edition-logs/tests-$index.log"
    echo "Checking: ${filter:-full suite}"
    if make -j"${JOBS:-4}" KEEP_TEMPS=1 check TESTS="$filter" 2>&1 | tee "$log"; then
        echo "PASS: ${filter:-full suite}"
    else
        echo "FAIL: ${filter:-full suite} (see $log)"
        failed=1
    fi
    python3 tools/complete_edition/summarize_tests.py "$log" > "${log%.log}.json"
    index=$((index+1))
done
exit "$failed"
