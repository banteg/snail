# initialize_high_score_entry

Seeds one 0x1fac0 replay/high-score record before a run or blank table entry is
used.

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
