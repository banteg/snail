# serialize_compact_high_score_record

This scratch is the forward direction for the compact ScoreA/B/C on-disk record.
It confirms the same `0x88 + replay_sample_count * 5` byte count and the same
three packed replay lanes as the deserializer.

Android exports the paired owner method as `cRSubSolution::Save(unsigned char*)`.
Together with `Load(cRSubSolutionHeader*)`, this identifies the Windows
receiver as the authored 0x1fac0-byte `SubSolution`, not the enclosing score
bank.

Current result: exact. The replay lane loops use indexed source/destination
access for the two packed word lanes and a pointer walk for the byte flags lane,
matching native register ownership while keeping the `int16[]`, `int16[]`,
`uint8[]` compact payload explicit.

2026-06-20 larger-chunk audit:
- Moving the lateral and delta-z source cursor declarations before the branch
  improves the focused match from 85.32% to 93.58% and preserves the 109/109
  instruction count. Removing the `lateral_count`/`delta_z_count` aliases is
  codegen-neutral at the improved score.
- Rewriting the word-lane source cursors as `ReplayRunRecord*` compiles
  identically to the old 85.32% baseline, so the improvement is the cursor
  lifetime, not the typed source view.
- 2026-06-20 follow-up: splitting each source cursor into a declaration before
  the branch and assignment inside the branch regresses to the old 85.32%
  source/destination swap. Reusing the top `sample_count` local for every
  payload bound and byte-count computation regresses to 20.28% by collapsing
  the native replay-count reloads and reshaping the whole scalar tail. Keep
  the accepted pre-branch source cursor initialization plus direct
  `replay_sample_count` loop bounds.
- Current chunk: promoted compact replay payload accessors onto
  `SubSolutionHeader` and rewrote the three output-lane bases through
  `lateral_samples()`, `delta_z_samples(count)`, and `flag_samples(count)`.
  This is codegen-neutral at 93.58%, but removes raw header-byte arithmetic
  from the paired serializer/deserializer without hiding the remaining register
  scheduling residual.
- Retried per-lane count aliases with the accessors; they are also
  codegen-neutral and were dropped to keep the accepted source shape minimal.
- 2026-06-20 exact pass: applying the deserializer's indexed word-lane insight
  to both lateral and delta-z output loops fixes the remaining count/cursor
  scheduling residuals. Focused Wibo is now 100.00%, 109/109 instructions,
  109/109 prefix, and one clean masked operand.
