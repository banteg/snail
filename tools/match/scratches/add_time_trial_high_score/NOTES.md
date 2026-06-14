# add_time_trial_high_score

`add_time_trial_high_score` @ 0x4178b0 records the just-finished Time Trial
result into the high-score bank. Cross-port symbols identify this as
`cRSubHighScore::AddTimeTrial(int, bool)`.

Behavior:

- Tags the result record as mode 2, stores the route index, and clears the
  replay cursor field.
- Failed/inactive route writes zero the record's timer total before copying it
  into the scratch/current-result slot at `this + 0x9080c8`.
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
