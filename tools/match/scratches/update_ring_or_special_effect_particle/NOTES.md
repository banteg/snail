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

2026-06-16 BN cross-check:

- The particle layout used here is compact and consistent with the source:
  sprite pointer at `+0x00`, parent pointer at `+0x04`, phase at `+0x14`,
  phase_step at `+0x18`, and radius at `+0x1c`.
- The parent offsets used here are position `+0x68/+0x6c/+0x70`, owner player
  `+0x84`, kind `+0x88`, and star-shower counter `+0x1e8`.
- `RingOrSpecialEffectParent` is now promoted to
  `tools/match/include/ring_special_effect_types.h` after corroboration from
  `emit_ring_star_shower` and `initialize_ring_or_special_effect_particles`.
- Do not promote `RingOrSpecialEffectParticle` yet: this updater needs
  `emit_ring_star_shower` declared as an `int` return to avoid an extra
  `movsx eax, al`, while the emitter itself is byte-return shaped. The
  initializer corroborates the data layout but does not resolve that method
  surface.
