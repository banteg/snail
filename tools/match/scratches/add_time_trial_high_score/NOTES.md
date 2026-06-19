# add_time_trial_high_score

`add_time_trial_high_score` @ 0x4178b0 records the just-finished Time Trial
result into the high-score bank. Cross-port symbols identify this as
`cRSubHighScore::AddTimeTrial(int, bool)`.

Behavior:

- Tags the result record as mode 2, stores the route index in
  `route_or_rank_index`, and clears the replay cursor field.
- Failed/inactive route writes zero the record's timer total before copying it
  into the `current_result_record` slot at `this + 0x9080c8`.
- Successful route writes also inspect the per-route record at
  `this + 0x2b8c88 + route_index * 0x1fac0`; the persistent route record is
  replaced only when the new time is lower than the stored time or the stored
  time is zero.
- After a persistent replacement, the route-index field is written again at
  `route_record + 0x40`.

Match status: 83.67% (49/49 instruction count, 20/49 exact prefix).

Residual:

- Native computes `route_index * 0x1fac0`, adds that stride into the `this`
  register (`ebp`), then uses `ebp + 0x2b8c88/90/c8` for both comparisons and
  the replacement copy.
- The plain source-shaped array indexing keeps `this` unmodified for the first
  compare (`fcomp [ecx + ebp + 0x2b8c90]`) and materializes `route_record`
  afterward (`lea ebp, [ecx + ebp + 0x2b8c88]`). Semantics are equivalent; the
  diff is route-record base materialization and branch-label distance.

Rejected source-shape probes:

- Explicit route-window pointer: recovered neither native register ownership nor
  the prefix, regressing to 55.10%.
- Function-scope `HighScoreBank* bank` and selected-bank reassignment: compiled
  identically to the baseline.
- Pointer/reference to `route_record->total_seconds`, local `record_seconds`,
  and split `goto` replacement gate: all compiled identically to the baseline.
- Local `route_seconds` value: changed x87 compare ordering and regressed to
  78.79%.
- 2026-06-18 shared-layout pass: the scratch now consumes
  `tools/match/include/high_score_bank.h` and `high_score_record.h`. The score
  remains 83.67%, so the shared layout did not change the known route-record
  base materialization residual.
- 2026-06-18 name-sync pass: `HighScoreRecord` exposes the `+0x08` lane as
  `total_seconds` first, with the score-bucket block as an alternate view. This
  keeps the time-trial helper and BN decompile aligned on the ordering key
  without changing layout or codegen.
- 2026-06-20 route-base retry: materializing a `HighScoreBank*` for the selected
  route and then taking `route_bank->time_trial_route_records`, or spelling the
  same address through an incremented `char* route_base`, are both codegen-neutral
  at 83.67%. Native still adds the route stride into the `this` register before
  the compare, so the current array-shaped source remains the least misleading
  expression of the recovered layout.
