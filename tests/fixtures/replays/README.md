# Original replay fixtures

Score bank files written by the original Windows game (`ScoreA.dat` =
postal, `ScoreB.dat` = challenge, `ScoreC.dat` = completion records with
the Time Trial ghost lane). Each high-score record embeds its replay as a
variable-length sample array in the compact format handled by
`serialize/deserialize_compact_high_score_record` (@ 0x440170/0x440020)
and the Zig codec in `zig/src/high_score.zig`.

To use with the port: copy into `artifacts/runtime/` (the port's runtime
root) — or point tests here directly. Differential runs against native
captures use `--preserve-bugs` (docs/rewrite/original-bugs.md).

Name fixtures by provenance, e.g. `ScoreA.tutorial-run-2026-06-12.dat`,
and note alongside each file what was played and on which level, plus the
matching frida trace filename if one was captured during the replay.
