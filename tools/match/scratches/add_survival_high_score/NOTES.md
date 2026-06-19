# add_survival_high_score

`add_survival_high_score` @ 0x417780 records a completed Challenge/Survival
result into the ordered top-ten bank and prepares the high-score entry frontend.

Behavior:

- Tags the incoming record as survival (`high_score_mode_tag = 1`), clears its
  route/rank and replay cursor fields, then copies the full 0x1fac0 record into
  both `current_result_record` and `survival_pending_record`.
- Scans `survival_records[0..9]` by descending `score`. If the run does not
  place, returns the rank cursor (`10`).
- If it places, shifts lower records into the spare eleventh storage slot,
  writes the new record at the selected rank, points the frontend
  `active_record_bank` at `survival_records`, and marks the pending entry as
  bank 1.

The extra `rank != -1` gate is source-shaped from native even though this local
rank search only produces non-negative ranks.

Match status: 66.67%, 81/84 instructions, 3/84 exact prefix, five masked
operands resolved.

Residual:

- Native keeps the bank owner in `ebp` and spills it before the rank scan.
  The current source-shaped shared-layout scratch assigns the bank owner to
  `ebx`, but preserves the top-tested score cursor and full record copies.
- The high-score frontend arm is semantically aligned, including the native
  `rank != -1` gate, but global reload and active-bank materialization differ
  in register ownership.
- 2026-06-20 high-score insertion pass: the arcade helper improved when its
  down-shift loop was spelled as a pre-tested `while`, but applying the same
  source shape here regressed survival to 55.95%. MSVC then kept constant `1`
  in `ebp` and left the bank in `ebx`, moving further away from native, so the
  survival scratch keeps the existing `do while` shift loop.
