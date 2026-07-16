# save_high_scores_and_config @ 0x417940

- Cross-port iOS symbols place `cRSubHighScore::MiniSave(int)` in
  `HighScore.o`. The Windows member likewise accepts one save-mask argument
  and serializes the three value-owned `SubSolution` banks before saving the
  shared config blob.
- The five native callsites at `0x40723a`, `0x40724d`, `0x40725f`,
  `0x407272`, and `0x407285` immediately prepare the next call or continue
  teardown; none consumes EAX.
- The only apparent return is the value left by the final
  `save_config_file` call. Removing the synthetic `char*` return produces the
  same 101-instruction object with all 19 masked operands clean, so the
  authored contract is `void` rather than a borrowed config pointer.

2026-07-16 compact persistence ownership:

- The tracked allocation is a byte buffer whose moving write cursors are
  `CompactHighScoreRecord*`; the three source ranges remain value-owned
  `SubSolution` arrays within `SubHighScore`.
- Recovered archive-shell prototypes keep byte counts as integers and buffers
  as `void*`/`char*`, removing stale frontend and completion-screen casts from
  IDA without narrowing shared helper ownership.
- Strict paired export and ownership health checks pass. Focused matching
  remains exact at 101/101 instructions with all 19 masked operands clean.
