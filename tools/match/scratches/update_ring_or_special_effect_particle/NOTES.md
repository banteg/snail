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
