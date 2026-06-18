# add_arcade_high_score

`add_arcade_high_score` @ 0x4176a0 records a completed Postal/Arcade result
into the ordered top-ten bank.

Behavior:

- Writes the incoming level argument to the record's `route_or_rank_index`, tags
  the scratch/current result as arcade (`high_score_mode_tag = 0`), and copies
  the full 0x1fac0 record into `HighScoreBank::current_result_record`.
- Scans `postal_records[0..9]` by descending `score`. If the new score does not
  place, returns the rank cursor (`10`).
- If it places, shifts lower records down through the spare eleventh storage
  slot, updates each shifted record's `route_or_rank_index`, copies the new
  record into the selected rank, and arms the high-score entry frontend state.

The scratch uses the shared `HighScoreBank` and `HighScoreRecord` layouts so
this helper, `add_survival_high_score`, `add_time_trial_high_score`, replay
launch, and `complete_subgame` all describe the same 0x1fac0 record.

Match status: 65.69%, 67/70 instructions, 15/70 exact prefix, one masked
operand resolved.

Residual:

- Native keeps the bank owner in a stack local before the rank scan and compares
  the score directly from memory. The source-shaped scratch caches the first
  postal score into `edi` and bottom-tests the cursor compare.
- Native reloads `g_game_base` around the frontend state writes with slightly
  different pop scheduling. The scratch uses the same frontend fields and
  repeated global accesses, but VC6 still orders those stores differently.
