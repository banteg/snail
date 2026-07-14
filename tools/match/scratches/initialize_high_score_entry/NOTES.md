# initialize_high_score_entry

Seeds one 0x1fac0 replay/high-score record before a run or blank table entry is
used. iOS and Android both preserve the authored owner/signature as
`cRSubSolution::ReSet(int, int, float, int, int, int)` in `HighScore.o`; the
Windows float argument is passed and stored through its raw 32-bit lane.

Recovered layout corrections:

- `player_name` is 0x14 bytes at `+0x54`; `+0x68` is `runtime_build_seed`.
- `replay_sample_count` is `+0x6c`.
- replay records start at `+0x70`, are 21600 six-byte entries, and have their
  per-entry `lateral_x`, `delta_z`, flags, and reserved byte fields.

2026-06-19 post-name-copy ordering:

- Exact match. Spelling the post-`rstrcpy_checked_ascii` stores in native order
  (`active = 0` before `runtime_build_flags = runtime_build_flags_value`) keeps
  the existing argument reload shape and removes the last one-instruction store
  swap without barriers, raw offset writes, or dummy temporaries.

2026-07-11 ownership pass:

- Promoted the complete 0x1fac0 layout from the provisional
  `HighScoreRecord` name to the authored `SubSolution` owner. The scratch stays
  exact at 40/40 instructions; the change is provenance and ownership, not a
  code-shape adjustment.

2026-07-14 process-root ownership:

- The default player name now comes through the canonical `GameRoot* g_game`
  owner and `GameRoot::players[0].player_name`. The former `g_game_base` cast
  duplicated an ownership boundary already proven by the root player array.
  Focused matching remains exact at 40/40 instructions with all three masked
  operands clean.
