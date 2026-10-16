#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/../.."
log_dir="build/complete-edition-logs/candidate"
mkdir -p "$log_dir"
filters=("test/battle/move_effect/embargo.c" "test/complete_edition_rewards.c" "test/battle/ai/ai_doubles.c" "test/battle/ai/ai_switching.c" "test/battle/move_effect/beat_up.c" "test/battle/move_effect/roost.c" "test/battle/ability/anger_shell.c" "test/battle/ability/berserk.c" "test/battle/ability/color_change.c" "test/battle/ability/pickpocket.c" "test/battle/ability/anticipation.c" "test/battle/ability/mirror_armor.c" "test/battle/ability/neutralizing_gas.c" "test/battle/sleep_clause.c" "test/battle/ability/sheer_force.c" "test/battle/hold_effect/life_orb.c" "test/battle/hold_effect/shell_bell.c" "test/battle/hold_effect/eject_button.c" "test/battle/hold_effect/red_card.c" "test/battle/ability/emergency_exit.c" "Complete Edition")
python3 tools/complete_edition/check_objects.py --repair emerald-test | tee "$log_dir/object-repair.log"
failed=0
index=0
for filter in "${filters[@]}"; do
    log="$log_dir/tests-$index.log"
    echo "Candidate family: $filter"
    if ! make -j"${JOBS:-4}" KEEP_TEMPS=1 check TESTS="$filter" 2>&1 | tee "$log"; then
        failed=1
    fi
    python3 tools/complete_edition/summarize_tests.py "$log" > "${log%.log}.json"
    python3 tools/complete_edition/check_objects.py emerald-test
    if ! python3 - "${log%.log}.json" <<'PY'
import json, sys
report = json.load(open(sys.argv[1]))
print("Native candidate:", report["statuses"], "complete:", report["complete"])
if not report["complete"]:
    sys.exit(2)
sys.exit(0 if report["no_failing_outcomes"] else 1)
PY
    then
        failed=1
    fi
    # A build error or interrupted process cannot provide a completed family.
    # Stop here rather than repeatedly retrying the same failed compilation.
    if ! python3 - "${log%.log}.json" <<'PY'
import json, sys
sys.exit(0 if json.load(open(sys.argv[1]))["complete"] else 1)
PY
    then
        exit 1
    fi
    index=$((index + 1))
done
exit "$failed"
