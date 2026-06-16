# emit_ring_star_shower @ 0x43e690

Live source map for the star burst emitted by
`update_ring_or_special_effect_particle` when the parent cadence counter is
zero.

Current match: 54.69%, 63 candidate instructions versus 65 target instructions,
with 9 clean masked operands. The scratch deliberately uses shared `sprite.h`,
`player.h`, and `ring_special_effect_types.h`, confirming the already-promoted
Sprite lanes used by this emitter:

- `progress`, `progress_step`, `size_start`, `size_end`, and `gravity_step`
- `velocity` and `position`
- parent `star_sprite_id` at `+0x1ec` from the shared
  `RingOrSpecialEffectParent`
- owner `Player::player_slot` at `+0x380`

Residual:

- Native reserves a `0x18` stack frame immediately after loading
  `g_render_flags`, keeps a stack zero lane for `velocity.z`, and stores the
  sine/cosine temporaries through explicit stack slots before writing
  `sprite->velocity`.
- The current source preserves the field behavior but compiles to a smaller
  stack frame, direct `velocity.z = 0`, and a different position-copy register
  schedule.

Rejected/source-shape probes:

- Replacing the shared headers with local POD `Sprite`/`Player` views compiled
  identically, so the mismatch is not caused by the promoted Sprite layout.
- A staged `Vector3 velocity` local improved only to 55.64% and still used a
  `0x0c` frame.
- A `float velocity[3]` local improved only to 56.25% and still used a `0x0c`
  frame.
- Adding a staged source-position vector reached 58.27% but moved farther from
  the native direct position copy, so the clearer shared-header source is kept.

Type consolidation:

- `RingOrSpecialEffectParent` is promoted in
  `tools/match/include/ring_special_effect_types.h`; this scratch adds
  `star_sprite_id +0x1ec`, while
  `update_ring_or_special_effect_particle` corroborates position, owner, kind,
  and star-shower counter offsets.
- `RingOrSpecialEffectParticle` stays local for now because its method
  signatures differ by callsite: this callee is byte-return shaped, while the
  updater must declare it as `int` to preserve codegen. The initializer now
  independently corroborates the `0x20` stride and data fields, but not the
  method return model.
