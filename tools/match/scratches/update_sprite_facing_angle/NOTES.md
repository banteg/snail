# update_sprite_facing_angle

Near-match for Sprite facing-angle refresh at `0x44e410`.

- Flag `0x400` enables throttled facing refresh through `+0x8c/+0x90`.
- When throttled, native recomputes the angle only when
  `facing_refresh_progress == 0.0f`; the previous nonzero interpretation was
  wrong.
- The recompute path uses `position - previous_position`, rotates that delta by
  the supplied transform matrix, then stores
  `atan2_positive(rotated.x, rotated.y) + 7.0685835f` into `+0x7c`.
- Remaining residual: 97.67%, 86/86 instructions, eight masked operands clean.
  The only mismatch is the stack slot used to spill the returned rotated `z`
  component before `atan2_positive`; avoid forcing this with an artificial
  one-field copy.

Rejected source-shaped probes:

- assigning the rotated result back into `delta` changed the local layout and
  expanded the effective recompute blocks;
- reordering the `rotated`, `delta_source`, and `delta` declarations was
  score-neutral and did not change the spill slot;
- keeping the returned `Vector3*`, copying it back into `delta`, and then using
  the pointer for `atan2_positive` forced a full rotated-vector copy and
  regressed the score to 56.67%.
- 2026-06-17 retest: the minimal `delta = *delta.rotate_vector_by_matrix(...)`
  spelling and the two-vector receiver/result spelling both regressed to 67.05%
  by moving the rotate receiver local and adding explicit X/Y stores. Moving
  `rotated` after the delta locals and putting `delta` first were score-neutral.
  The remaining mismatch is still only the dead returned-Z spill slot
  (`[esp+0x20]` native versus `[esp+0x14]` candidate), not evidence for a
  different `Sprite` field or transform type.

2026-06-16 BN cross-check: the decompile agrees with the current field model
(`previous_position`, `position`, `facing_angle`, and the refresh progress/step
pair). The residual remains only the rotated `z` spill slot after
`rotate_vector_by_matrix`; it is not evidence for another Sprite field or a
different matrix type.

2026-06-16 five-target audit: the disassembly confirms flag `0x400` is tested
through the high byte of `Sprite::flags`, so the current `flags +0x04` lane and
refresh fields `+0x8c/+0x90` remain the right shared names.
