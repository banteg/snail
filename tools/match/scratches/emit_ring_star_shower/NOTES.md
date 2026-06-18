# emit_ring_star_shower @ 0x43e690

Live source map for the star burst emitted by
`update_ring_or_special_effect_particle` when the parent cadence counter is
zero.

Current match: 74.42%, 64 candidate instructions versus 65 target instructions,
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
  frame, but now matches the native idea of filling a local velocity vector
  with unscaled orbit components before applying the `0.30000001f` velocity
  scale and copying the vector to `sprite->velocity`.
- The position copy is intentionally dword-shaped: native copies x/y/z from
  the parent sprite position and stores gravity zero before writing z. Native
  leaves the low byte of the copied z dword in `al`, but the only known caller
  ignores it. The `int*` spelling keeps that
  relationship explicit and removes the earlier extra source-z byte reload.

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
- Widening the old local result to `int` to chase the full Z-word return regressed
  to 56.45% by adding an extra prologue zeroing instruction; keep the byte
  result shape if a return-typed probe is ever needed again.
- 2026-06-16 vector-fill correction: combining the direct trig-expression form
  with a local `Vector3 velocity`, then scaling `velocity.x` and `velocity.y`
  in place before `star->velocity = velocity`, improves the focused match from
  58.54% to 71.21%. A separate `scaled_x` / `scaled_y` spelling compiled
  identically to the earlier 67.69% vector-copy variant, so the in-place vector
  scaling is kept as the better source-shaped form.
- 2026-06-16 dword position-copy correction: spelling the parent sprite
  position copy as three dword lanes improves the focused match from 71.21% to
  74.42% and removes three candidate instructions at the tail. Explicit
  unscaled velocity x/y locals regressed to 70.87%, and an explicit sprite
  flag read-modify-write compiled identically to the simple `flags |= 0x800`
  source, so neither variant is kept.
- 2026-06-16 direct destination retry: removing the `star_position_words`
  destination pointer and writing `((int*)&star->position)[0..2]` directly
  compiled identically at 74.42%. This confirms the remaining tail residual is
  not solved by the destination pointer spelling; keep the current clearer
  dword-position-copy source.

Type consolidation:

- `RingOrSpecialEffectParent` and `RingOrSpecialEffectParticle` are promoted in
  `tools/match/include/ring_special_effect_types.h`; this scratch confirms the
  promoted particle `sprite`, `parent`, `phase`, and `radius` fields plus parent
  `star_sprite_id +0x1ec`.
- 2026-06-16 return-type correction: the emitter itself is now modeled as
  `void`. Every known callsite ignores the helper return; the native low-byte
  `al` result is an incidental position-copy artifact, not a meaningful
  gameplay value. Focused Wibo remains 74.42%, and the caller remains 96.36%.
- 2026-06-18 BN prototype sync: the durable BN prototype is now
  `void __thiscall emit_ring_star_shower(RingOrSpecialEffectParticle*, Player*)`.
  This resolves `particle->phase`, `particle->radius`, `particle->parent`,
  `owner->player_slot`, and Sprite position/velocity fields in the BN export;
  the match residual stays the known stack-frame/source-shape issue.
