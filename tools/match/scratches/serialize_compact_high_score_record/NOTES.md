# serialize_compact_high_score_record

This scratch is the forward direction for the compact ScoreA/B/C on-disk record.
It confirms the same `0x88 + replay_sample_count * 5` byte count and the same
three packed replay lanes as the deserializer.

Current residual:
- the replay lane loops are semantically correct pointer walks, but VC6 assigns
  the source and destination cursors to ECX/EDX opposite to native for the two
  word lanes
- no masked operand mismatches are present
