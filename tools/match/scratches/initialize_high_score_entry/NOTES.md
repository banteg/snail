# initialize_high_score_entry

Seeds one 0x1fac0 replay/high-score record before a run or blank table entry is
used.

Recovered layout corrections:

- `player_name` is 0x14 bytes at `+0x54`; `+0x68` is `runtime_seed`.
- `completion_count` is `+0x6c`.
- replay records start at `+0x70`, are 21600 six-byte entries, and have their
  per-entry flags byte at `+0x04`; index 0's flags live at record offset
  `+0x74`.
