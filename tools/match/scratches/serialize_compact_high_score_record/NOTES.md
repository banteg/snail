# serialize_compact_high_score_record

This scratch is the forward direction for the compact ScoreA/B/C on-disk record.
It confirms the same `0x88 + replay_sample_count * 5` byte count and the same
three packed replay lanes as the deserializer.

Current residual:
- the replay lane loops are semantically correct pointer walks. The accepted
  word-lane shape now gives VC6 the native source/destination cursor ownership
  (`source` in `ecx`, compact output in `edx`), but the candidate still keeps
  the replay count/test in `esi` and hoists the source cursor before the empty
  branch, while native tests `ecx` and materializes the source cursor after the
  `jle`.
- no masked operand mismatches are present

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
