# load_high_scores_from_file

Loads one encoded ScoreA/B/C file, walks its variable-length compact records,
and dispatches each expanded solution into the postal, survival, or per-route
time-trial array owned by `SubHighScore`.

2026-07-16 compact persistence ownership:

- The generic archive helper correctly remains
  `void* load_file_bytes(char*, int32_t*)`; only this caller's returned cursor
  is a `CompactHighScoreRecord*`. Encoding the local type in both decompilers
  avoids falsely narrowing the shared helper ABI.
- `bank_selector`, `entry_index`, and `byte_count` now render as fields in both
  Binary Ninja and IDA, and each destination is a value-owned `SubSolution`
  array within `SubHighScore`.
- The archive-shell replay also restores the real byte-buffer/count contracts
  for the XOR, file-write, and config-save helpers.
- Strict paired export and ownership health checks pass. Focused matching is
  exact at 71/71 instructions with all four masked operands clean.
