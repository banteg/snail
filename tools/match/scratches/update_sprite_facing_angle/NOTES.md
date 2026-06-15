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
