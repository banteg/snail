# emit_ring_star_shower @ 0x43e690

Live source map for the star burst emitted by
`update_ring_or_special_effect_particle` when the parent cadence counter is
zero.

Current match: 71.21%, 67 candidate instructions versus 65 target instructions,
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
  `g_render_flags`. The current source still compiles to a smaller `0x0c`
  frame and a different position-copy register schedule, but now matches the
  native idea of filling a local velocity vector with unscaled orbit components
  before applying the `0.30000001f` velocity scale and copying the vector to
  `sprite->velocity`.

Rejected/source-shape probes:

- Replacing the shared headers with local POD `Sprite`/`Player` views compiled
  identically, so the mismatch is not caused by the promoted Sprite layout.
- An earlier staged `Vector3 velocity` local with separate trig temporaries
  improved only to 55.64% and still used a `0x0c` frame.
- A `float velocity[3]` local improved only to 56.25% and still used a `0x0c`
  frame.
- Adding a staged source-position vector reached 58.27% but moved farther from
  the native direct position copy, so the clearer shared-header source is kept.
- A direct trig-expression form plus separate unscaled `velocity_x` and
  `velocity_y` locals previously improved the scratch to 58.54% by matching the
  native call argument and scale order. The current vector-fill form preserves
  that source-level idea while recovering more of the native velocity copy
  shape.
- Widening the local result to `int` to chase the full Z-word return regressed
  to 56.45% by adding an extra prologue zeroing instruction; keep the byte
  result shape.
- 2026-06-16 vector-fill correction: combining the direct trig-expression form
  with a local `Vector3 velocity`, then scaling `velocity.x` and `velocity.y`
  in place before `star->velocity = velocity`, improves the focused match from
  58.54% to 71.21%. A separate `scaled_x` / `scaled_y` spelling compiled
  identically to the earlier 67.69% vector-copy variant, so the in-place vector
  scaling is kept as the better source-shaped form.

Type consolidation:

- `RingOrSpecialEffectParent` and `RingOrSpecialEffectParticle` are promoted in
  `tools/match/include/ring_special_effect_types.h`; this scratch confirms the
  promoted particle `sprite`, `parent`, `phase`, and `radius` fields plus parent
  `star_sprite_id +0x1ec`.
- The emitter itself is byte-return shaped (`char`). The child updater is
  promoted as `void` because every known callsite ignores the helper return;
  modeling it as `char` or `int` is only a codegen surface, not a meaningful
  gameplay value.
