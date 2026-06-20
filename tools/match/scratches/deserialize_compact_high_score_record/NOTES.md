# deserialize_compact_high_score_record

This scratch recovers the compact ScoreA/B/C record bridge into the expanded
`HighScoreRecord` layout. The scalar block, checksum, player name, and replay
payload offsets are source-shaped; the remaining mismatch is a pure ECX/EDX
cursor swap in the second replay lane copy loop.

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
  `CompactHighScoreRecord` accessors for lateral, delta-z, and flag lanes. The
  rewrite is codegen-neutral at 92.98% and keeps the masked audit clean while
  making the packed `int16[]`, `int16[]`, `uint8[]` layout explicit for both
  persistence directions.
- Retried direct `replay_sample_count` spelling for the delta-z packed source
  offset after adding the accessors; it stayed codegen-neutral and leaves the
  same native `ecx` count / candidate `edx` count ownership residual.
