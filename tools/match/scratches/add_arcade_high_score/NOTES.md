# add_arcade_high_score

`add_arcade_high_score` @ 0x4176a0 records a completed Postal/Arcade result
into the ordered top-ten bank.

Behavior:

- Writes the incoming level argument to the record's `route_or_rank_index`, tags
  the scratch/current result as arcade (`high_score_mode_tag = 0`), and copies
  the full 0x1fac0 record into `SubHighScore::current_result_record`.
- Scans `postal_records[0..9]` by descending `score`. If the new score does not
  place, returns the rank cursor (`10`).
- If it places, shifts lower records down through the spare eleventh storage
  slot, updates each shifted record's `route_or_rank_index`, copies the new
  record into the selected rank, and arms the high-score entry frontend state.

The scratch uses the shared `SubHighScore` and `SubSolution` layouts so
this helper, `add_survival_high_score`, `add_time_trial_high_score`, replay
launch, and `complete_subgame` all describe the same 0x1fac0 record.
Android and iOS retain this owner method as
`cRSubHighScore::AddArcade(int)`; Windows passes the working solution pointer
explicitly before value-copying it into the owned postal array.

Match status: 100.00%, 70/70 instructions, full exact prefix, four masked
operands resolved.

Accepted source-shape notes:

- 2026-06-20 high-score insertion pass: changing the down-shift loop from
  `do while` to `while (shift_rank > rank)` recovered the native pre-test
  (`cmp eax, ebx; jge`) and improved the score from 65.69% to 80.58%.
- Moving the not-placed return out of the inner scan loop stopped VC6 from
  peeling the first score comparison and improved the prefix from 15 to 28
  instructions, but an ordinary `break` still let the optimizer remove the
  shift-loop guard.
- The proof shape is a bounded `while (rank < 10)` scan whose score comparison
  exits through `goto insert_record`; the no-place path falls through to
  `return rank`. This preserves the native scan branch and keeps the later
  shift guard because the insertion label is reached from the comparison.
- Returning a `GameRoot*` local from the final `high_score_entry_bank`
  store removes the otherwise extra trailing `g_game_base` reload and matches
  the native frontend state write epilogue.

Rejected/neutral source-shape probes:

- Rewriting the scan as `while (score <= *score_cursor)` was codegen-neutral at
  80.58%; VC6 still cached the first postal score in `edi` and bottom-tested the
  loop.
- Walking a `SubSolution*` cursor and comparing `record->score` directly
  were also neutral at 80.58%.
- Sharing one `shift_rank` limit variable between the scan and shift loop
  regressed to 63.38% by pushing `ebx` in the prologue.

2026-07-10 cRPlayer state ownership: the four frontend writes now target
`GameRoot::players[0]` directly (`frontend_state`, pending byte, entry rank,
and entry bank). The owner promotion is byte-neutral at the exact 70/70 anchor.
