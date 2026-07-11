# emit_ring_star_shower @ 0x43e690

Live source map for the star burst emitted by
`update_ring_or_special_effect_particle` when the parent cadence counter is
zero.

Current match: 100.00%, 65 candidate instructions versus 65 target
instructions, with a 65/65 common prefix and 9 clean masked operands. The
scratch deliberately uses shared `sprite.h`, `player.h`, and
`ring_special_effect_types.h`, confirming the already-promoted Sprite lanes
used by this emitter:

- `progress`, `progress_step`, `size_start`, `size_end`, and `gravity_step`
- `velocity` and `position`
- parent `star_sprite_id` at `+0x1ec` from the shared
  `RingOrSpecialEffectParent`
- owner `Player::player_slot` at `+0x380`

Resolved:

- A second semantic `Vector3` for the unscaled orbit velocity recovers native's
  `0x18` stack frame.
- Direct `star->position = sprite->position` assignment preserves the aggregate
  copy registers and recovers native's gravity-before-z store schedule.

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
  not solved by the destination pointer spelling alone; the dword-position-copy
  form stayed as the best source until the later `Vector3` assignment probe.
- 2026-06-20 position-copy correction: spelling the emitted star position copy
  as `Vector3* source_position = &sprite->position; Vector3* star_position =
  &star->position; *star_position = *source_position;` improves the focused
  match from 74.42% to 90.77%. This recovers the native source pointer in `eax`,
  destination pointer in `ecx`, sprite-flag read/write register, and 65/65
  instruction count. Adding only named `Vector3*` source/destination pointers
  around the old dword copy compiled identically at 74.42%, so the win is the
  semantic vector assignment rather than pointer naming alone.
- 2026-06-20 rejected gravity-order probes: splitting the assignment into
  `x/y/z` field stores regressed to 74.42% by losing the native destination
  pointer shape and using an x87 z copy. Naming separate unscaled velocity
  locals regressed to 85.94% by disturbing the x87 scale schedule. Staging
  `sprite->position` into a local `Vector3` regressed to 79.39% and still kept
  the smaller `0x0c` frame, so the remaining `0x18` frame residual is not
  explained by a source-position local.
- 2026-06-20 larger ring-family retry: focused Wibo still reports 90.77%,
  65/65 candidate/target instructions, 1/65 prefix, and 9 clean masked
  operands. Naming an explicit unscaled sine-x local is codegen-neutral overall:
  it only moves the temporary spill to a different candidate stack offset while
  keeping the `0x0c` frame. A semantic `float source_z` tail and a dword
  `source_z_bits` tail both regress to 74.42% by losing the aggregate
  vector-copy register shape, even though they place the gravity store before
  the z write. Keep the semantic `*star_position = *source_position` copy until
  a real source-lifetime lead explains native's `0x18` frame.
- 2026-06-20 allocation/tail lifetime retry: explicit `owner_slot` and
  `star_sprite_id` locals regress to 58.46% by changing register ownership from
  allocation through the velocity and position-copy blocks while still keeping
  the smaller `0x0c` frame. Naming `Sprite* source_sprite = sprite` before the
  aggregate position copy is codegen-neutral at 90.77% and leaves the same
  gravity-before-z residual. The remaining mismatch is therefore not explained
  by allocation-argument locals or by a missing source-sprite lifetime.

- 2026-06-20 exact-match pass: staging the unscaled sine/cosine results in
  `Vector3 orbit_velocity`, scaling into `velocity`, and using direct Sprite
  position assignment improves focused Wibo from `90.77%` to `100.00%`.
  Candidate and target are both 65 instructions, the common prefix is 65/65,
  and all 9 masked operands audit cleanly.

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
- 2026-06-19 family retry: focused Wibo still reports 74.42%, 64/65
  candidate/target instructions, and 9 clean masked operands. Naming an
  explicit `orbit_x` local, spelling the flag update through an unsigned
  temporary, and adding named source/destination position pointers all compile
  identically. Direct `star->position` field stores regress to 73.85% by
  splitting source sprite reloads, and explicit sine/cosine phase locals
  regress to 59.09% by materializing extra argument stores and disturbing the
  scratch push. Keep the dword position-copy baseline.

## 2026-07-11 authored owner promotion

The scratch now defines the exact method on `SubRingStar`, matching the iOS
`cRSubRingStar::Shower(cRSubGoldy*)` symbol. Its `parent` pointer is a borrowed
`SubRing*`, while its sprite remains a SpriteManager allocation. Matching stays
exact at 65/65 instructions with nine clean operands.
