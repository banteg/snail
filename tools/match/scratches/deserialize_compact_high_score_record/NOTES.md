# deserialize_compact_high_score_record

This scratch recovers the compact ScoreA/B/C record bridge into the expanded
`HighScoreRecord` layout. The scalar block, checksum, player name, and replay
payload offsets are source-shaped; the remaining mismatch is a pure ECX/EDX
cursor swap in the second replay lane copy loop.

Evidence from the paired serializer:
- compact header size is `0x88`
- checksum is `(score * score) ^ 0xdeadbabe`
- replay payload is packed as `int16 lateral_x[]`, `int16 secondary_lane_raw[]`,
  then byte `flags[]`
- compact load zero-extends each flags byte into the expanded record's `+0x04`
  word, clearing the reserved byte at `+0x05`
