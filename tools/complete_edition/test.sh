#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/../.."
profile="focused"
if [[ "${1:-}" == "--full" ]]; then
    profile="full"
fi
log_dir="build/complete-edition-logs/$profile"
mkdir -p "$log_dir"
python3 tools/complete_edition/validate.py | tee "$log_dir/placements.log"
python3 tools/complete_edition/check_objects.py --repair emerald-test | tee "$log_dir/test-object-repair.log"
filters=("Complete Edition" "test/pokemon.c" "test/daycare.c" "test/save.c" "test/battle/trainer_control.c" "test/battle/capture.c" "test/battle/wild_battle.c" "test/battle/ability/lightning_rod.c" "test/battle/ability/storm_drain.c" "test/battle/ability/filter.c" "test/battle/ability/iron_fist.c" "test/battle/move_effect/charge.c" "test/battle/move_effect/sleep.c" "test/battle/move_effect/dark_void.c" "test/battle/ability/forewarn.c")
if [[ "${1:-}" == "--full" ]]; then
    filters=("")
fi
index=0
failed=0
for filter in "${filters[@]}"; do
    log="$log_dir/tests-$index.log"
    rm -f "${log%.log}.json"
    echo "Checking: ${filter:-full suite}"
    if make -j"${JOBS:-4}" KEEP_TEMPS=1 check TESTS="$filter" 2>&1 | tee "$log"; then
        echo "PASS: ${filter:-full suite}"
    else
        echo "FAIL: ${filter:-full suite} (see $log)"
        failed=1
    fi
    python3 tools/complete_edition/summarize_tests.py "$log" > "${log%.log}.json"
    if ! python3 tools/complete_edition/check_objects.py emerald-test; then
        failed=1
    fi
    if ! python3 - "${log%.log}.json" <<'PY'
import json
import sys
report = json.load(open(sys.argv[1]))
sys.exit(0 if report["no_failing_outcomes"] else 1)
PY
    then
        echo "Verification incomplete or failed: $log"
        failed=1
    fi
    index=$((index+1))
done
exit "$failed"
