"""Regression tests for trustworthy native audit summaries."""
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

SCRIPT = Path(__file__).with_name("summarize_tests.py")


class SummaryTests(unittest.TestCase):
    def summarize(self, text):
        with tempfile.TemporaryDirectory() as directory:
            log = Path(directory) / "native.log"
            log.write_text(text, encoding="utf-8")
            result = subprocess.run([sys.executable, str(SCRIPT), str(log)],
                                    check=True, capture_output=True, text=True)
            return json.loads(result.stdout)

    def test_accepted_outcomes_and_expected_crash(self):
        rows = ["PASS", "EXPECTED_FAIL", "KNOWN_FAILING", "ASSUMPTION_FAIL", "TO_DO",
                "\x1b[32mCRASH\x1b[0m"]
        log = "".join(f"[0] case {i}: {status}\n" for i, status in enumerate(rows))
        report = self.summarize(log + "- Tests TOTAL: 6\n")
        self.assertTrue(report["no_failing_outcomes"])
        self.assertEqual(report["expected_crashes"], 1)
        self.assertEqual(len(report["known_failures"]), 1)

    def test_unexpected_and_unknown_outcomes_fail(self):
        for status in ("FAIL", "FLAKY", "TIMEOUT", "INVALID", "ERROR", "CRASH",
                       "\x1b[31mCRASH\x1b[0m", "UNKNOWN", "NEW_STATUS",
                       "UNEXPECTED_FAIL_LINE", "EXPECTED_FAIL_PASS", "KNOWN_FAILING_PASS"):
            with self.subTest(status=status):
                report = self.summarize(f"[0] case: {status}\n- Tests TOTAL: 1\n")
                self.assertFalse(report["no_failing_outcomes"])
                self.assertEqual(report["failing_outcomes"], 1)

    def test_partial_empty_and_mismatched_runs_fail(self):
        for log in ("", "[0] case: PASS\n", "- Tests TOTAL: 0\n",
                    "[0] case: PASS\n- Tests TOTAL: 2\n"):
            with self.subTest(log=log):
                self.assertFalse(self.summarize(log)["no_failing_outcomes"])

    def test_footer_failures_cannot_be_hidden_by_passing_rows(self):
        for footer in ("- Tests FAILED: 1", "- EXPECTED_FAIL_PASSING: 1"):
            with self.subTest(footer=footer):
                report = self.summarize("[0] case: PASS\n" + footer + "\n- Tests TOTAL: 1\n")
                self.assertFalse(report["no_failing_outcomes"])
                self.assertEqual(report["footer_failures"], 1)


if __name__ == "__main__":
    unittest.main()
