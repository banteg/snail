# update_ring_or_special_effect_particle @ 0x43e780

This helper advances one child sprite in a ring or special-effect halo.

Semantics:

- advance the child phase by `phase_step` unless the parent kind is `3`
- wrap the phase once when it exceeds tau
- place the sprite at the parent's XY position plus a circular
  `sin/cos(phase) * radius` orbit, copying the parent's Z lane
- emit the small star-shower sprite when the parent cadence lane at `+0x1e8`
  is zero

Match status: 96.36%, pinned.

Residual:

- Native adds the sine-derived X offset from `[parent + 0x68]` before
  materializing `parent_position = parent + 0x68`; the clean typed pointer
  spelling materializes the pointer first and then reads `[parent_position]`.
  Instruction count and data flow are otherwise aligned.

Rejected source-shape probe:

- Directly reading `live_owner->position.x` before creating the typed
  `owner_position` pointer regressed to 89.91% because MSVC moved the radius
  multiply before reloading the parent/sprite pointers.
- Retesting the narrower direct-X-only spelling reproduced the same 89.91%
  regression; keep the typed parent-position pointer despite the one-instruction
  materialization-order residual.

2026-06-16 BN cross-check:

- The particle layout used here is compact and consistent with the source:
  sprite pointer at `+0x00`, parent pointer at `+0x04`, phase at `+0x14`,
  phase_step at `+0x18`, and radius at `+0x1c`.
- The parent offsets used here are position `+0x68/+0x6c/+0x70`, owner player
  `+0x84`, kind `+0x88`, and star-shower counter `+0x1e8`.
- `RingOrSpecialEffectParent` is now promoted to
  `tools/match/include/ring_special_effect_types.h` after corroboration from
  `emit_ring_star_shower` and `initialize_ring_or_special_effect_particles`.
- Parent `position +0x68` is now consumed as inherited
  `RenderableBod::transform.position`; the runtime initializer, spawner, parent
  updater, and collision consumer confirm the transform rows live at parent
  `+0x38..+0x77`.
- `RingOrSpecialEffectParticle` is now promoted in
  `tools/match/include/ring_special_effect_types.h`. The earlier apparent
  return-type conflict is resolved by treating this updater as a side-effect-only
  `void` helper; `emit_ring_star_shower` is also modeled as `void` because all
  known callsites ignore the incidental byte result.
