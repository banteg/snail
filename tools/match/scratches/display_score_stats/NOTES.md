# display_score_stats @ 0x4403c0

`display_score_stats` reports the six score buckets accumulated by
`add_subgoldy_score` before `complete_subgame` snapshots the final result.

The function is source-shaped:

- return `0` immediately when the total score bucket at `+0x2e4` is zero
- print the total score header through the stripped release `debug_report_stub`
- print each score bucket as `(bucket * 100) / total`
- finish with the shared newline string at `data_4a44cc`

`data_4a44cc` is the literal `"\n"` in the executable data section, also used
by the warning/error report helpers, so the scratch keeps the real literal
instead of inventing a placeholder global.

Match status: 90.28%, pinned.

Residual:

- Native coalesces the cdecl cleanup for all eight report calls into one
  `add esp, 0x3c` at the end of the non-zero path. The standard
  `msvc6.5 /O2 /G5 /W3` source shape emits `add esp, 0x8` after each formatted
  call and `add esp, 0x4` after the final newline call.
- Because of that cleanup split, the compiler also duplicates the zero-return
  epilogue instead of sharing the native `pop esi; ret` tail. The value in
  `eax` is still the tested zero score.
