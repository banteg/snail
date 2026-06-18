# initialize_high_score_entry

Seeds one 0x1fac0 replay/high-score record before a run or blank table entry is
used.

Recovered layout corrections:

- `player_name` is 0x14 bytes at `+0x54`; `+0x68` is `runtime_build_seed`.
- `replay_sample_count` is `+0x6c`.
- replay records start at `+0x70`, are 21600 six-byte entries, and have their
  per-entry `lateral_x`, `delta_z`, flags, and reserved byte fields.

2026-06-18 post-name-copy scheduling:

- The focused Wibo diff is 97.50%, with the exact prefix extended to 26/40.
- The only remaining residual is one store-order swap after
  `rstrcpy_checked_ascii`: native clears `active` before storing
  `runtime_build_flags`, while VC6 keeps the flags store first.
  Snapshot-local and alternate store-order variants did not remove that swap
  cleanly, so leave it as scheduling debt rather than forcing it with barriers
  or raw offset writes.
