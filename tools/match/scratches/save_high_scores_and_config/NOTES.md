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

## 2026-07-25 persistence record cursor ownership

Each ScoreA/B/C serialization pass borrows one `SubSolution` from its
`SubHighScore`-owned array. Native advances EDI by exactly `0x1fac0` after
testing and optionally serializing the current record. Binary Ninja had
promoted those element cursors to pointers to the whole 11- or 51-record
array, forcing owner-subtraction expressions just to read `active`.

The exact SSA identities (`RegisterVariableSourceType`, storage `73`, indices
`39`, `118`, and `196`) now replay as the postal, survival, and time-trial
`SubSolution*` cursors. The tracked decompile consequently tests
`cursor->active`, passes that borrowed record directly to
`serialize_compact_high_score_record`, and advances by one record. IDA already
showed the same three element-pointer lifetimes independently.

Reanalysis also exposes a pre-existing Binary Ninja constant-rendering
ambiguity at the allocation call. Native pushes the scalar immediate
`0x4c4b40` (5,000,000), and `allocate_tracked_memory` accepts an `int32_t`
size. Because that numeric value happens to fall inside the real 500-entry
`g_texture_refs` address range, default BN HLIL presented it as an interior
address even though MLIL retains the literal scalar and IDA labels the same
immediate as the save buffer size. A guarded integer-token display replay now
pins the exact `push 0x4c4b40` operand to unsigned hexadecimal form and rejects
any native-byte or HLIL-shape drift. The tracked decompile therefore preserves
the scalar size and infers no texture-list ownership.

The focused replay verifies all three enclosing owner sizes before applying
the borrows. Matching source is unchanged and remains exact at 101/101
instructions with all 19 masked operands clean.
