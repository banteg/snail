# emit_ring_star_shower @ 0x43e690

Live source map for the star burst emitted by
`update_ring_or_special_effect_particle` when the parent cadence counter is
zero.

Current match: 58.54%, 58 candidate instructions versus 65 target instructions,
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
- The current source now matches the direct `phase + offset` trig-call argument
  spelling and computes the unscaled X/Y velocities before the 0.3 scale, but
  still compiles to a smaller stack frame, direct `velocity.z = 0`, and a
  different position-copy register schedule.

Rejected/source-shape probes:

- Replacing the shared headers with local POD `Sprite`/`Player` views compiled
  identically, so the mismatch is not caused by the promoted Sprite layout.
- A staged `Vector3 velocity` local improved only to 55.64% and still used a
  `0x0c` frame.
- A `float velocity[3]` local improved only to 56.25% and still used a `0x0c`
  frame.
- Adding a staged source-position vector reached 58.27% but moved farther from
  the native direct position copy, so the clearer shared-header source is kept.
- A direct trig-expression form plus separate unscaled `velocity_x` and
  `velocity_y` locals improves to the current 58.54% by matching the native call
  argument and scale order. This is retained because it is a plausible original
  source spelling and not a dummy scheduling artifact.
- Widening the local result to `int` to chase the full Z-word return regressed
  to 56.45% by adding an extra prologue zeroing instruction; keep the byte
  result shape.

Type consolidation:

- `RingOrSpecialEffectParent` and `RingOrSpecialEffectParticle` are promoted in
  `tools/match/include/ring_special_effect_types.h`; this scratch confirms the
  promoted particle `sprite`, `parent`, `phase`, and `radius` fields plus parent
  `star_sprite_id +0x1ec`.
- The emitter itself is byte-return shaped (`char`). The child updater is
  promoted as `void` because every known callsite ignores the helper return;
  modeling it as `char` or `int` is only a codegen surface, not a meaningful
  gameplay value.
