# deserialize_compact_high_score_record

This scratch recovers the compact ScoreA/B/C record bridge into the expanded
`SubSolution` layout. The scalar block, checksum, player name, and replay
payload offsets are exact.

Android exports this operation as
`cRSubSolution::Load(cRSubSolutionHeader*)`, confirming both the expanded
receiver and compact header owners independently of the Windows match.

Evidence from the paired serializer:
- compact header size is `0x88`
- checksum is `(score * score) ^ 0xdeadbabe`
- replay payload is packed as `int16 lateral_x[]`, `int16 delta_z[]`,
  then byte `flags[]`
- compact load zero-extends each flags byte into the expanded record's `+0x04`
  word, clearing the reserved byte at `+0x05`

2026-06-20 larger-chunk audit:
- Moving the second-lane destination cursor declaration before the packed
  source cursor regresses to 86.84% and disturbs the flags loop. It does not
  explain the native `source_delta_z` in EDX / destination in ECX ownership.
- Removing the `delta_z_count` alias and using `replay_sample_count` directly
  is codegen-neutral at 92.98%; the ECX/EDX cursor swap remains the only
  localized mismatch.
- 2026-06-20 follow-up: moving the second-lane packed source cursor assignment
  inside the non-empty branch regresses to 90.35% by moving the loop index into
  `edx` and changing the source/destination setup order. Rewriting the
  destination as a `ReplayRunRecord*` field store is codegen-neutral at 92.98%.
  Keep the current raw `short*` destination and pre-branch packed source cursor
  shape.
- Current chunk: the compact payload bases now use shared
  `SubSolutionHeader` accessors for lateral, delta-z, and flag lanes. The
  rewrite is codegen-neutral at 92.98% and keeps the masked audit clean while
  making the packed `int16[]`, `int16[]`, `uint8[]` layout explicit for both
  persistence directions.
- Retried direct `replay_sample_count` spelling for the delta-z packed source
  offset after adding the accessors; it stayed codegen-neutral and leaves the
  same native `ecx` count / candidate `edx` count ownership residual.
- 2026-06-20 exact pass: rewriting only the second word lane as indexed source
  and destination access (`run_records[i].delta_z = source_delta_z[i]`) recovers
  the native count/source/destination register ownership without changing the
  packed payload layout. Focused Wibo is now 100.00%, 114/114 instructions,
  114/114 prefix, and one clean masked operand.

2026-07-16 persistence ownership replay:

- Recovered `CompactHighScoreRecord` as the stable 0x88-byte on-disk prefix and
  kept its variable replay tail honest as a one-byte declaration sentinel. The
  record's actual byte count remains `0x88 + replay_sample_count * 5`.
- Replaced ambiguous raw scalar lanes with the named `SubSolutionScalar`
  union, preserving both integer bits and float meaning without anonymous-union
  syntax that either decompiler renders unreliably.
- Binary Ninja now preserves named lateral, delta-z, and flag cursors; IDA
  renders the same `SubSolution`/`CompactHighScoreRecord` fields and replay
  arrays. Strict paired export and ownership health checks pass.
- No source-shape changes or matching tricks were needed: focused matching
  remains exact at 114/114 instructions with the masked operand clean.
