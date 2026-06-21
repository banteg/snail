# Source-shaped pinned match

`spawn_golb_smoke` currently matches at 84.29%, 68 candidate instructions versus
72 target instructions, with a 43/72 exact prefix.

The scratch covers the recovered smoke producer behavior:

- allocate sprite id `128` for the owning player slot;
- set the smoke flag bit, clear progress lanes, and derive progress/lifetime
  steps from `game->subgame_rate`;
- copy white RGBA into the sprite color, seed scale `0.1f` by `0.5f`;
- scale the Golb velocity by `0.40000001f`, clear the gravity lane, and copy
  the caller position into the sprite.

The remaining residual is source-shape/codegen, not a known semantic gap. The
raw tail now keeps native color and scale stores at the sprite base. Native
still creates a velocity pointer and advances the position base before the
velocity stores, while the candidate stores those lanes through direct
`sprite + offset` forms. The final velocity x/y/z x87 staging also differs,
while the values and writes are covered.

Rejected source-shaped probes:

- explicit RGBA field copies through an `out_color` pointer regressed the score
  to 65.71% by changing the color copy and velocity x87 schedule;
- separate `velocity_x/velocity_y/velocity_z` scalar locals plus an earlier
  `out_velocity` pointer grew the frame to `0x14`, reordered the x87 stack, and
  regressed the score to 61.87%;
- explicit velocity/position output pointers were score-neutral at the time and
  matched the decompiler's clearer source view; this typed-output shape is now
  superseded by the raw float-lane tail below.
- 2026-06-16 cleanup: the local `Game` view is now a `class` to match
  `player.h` and remove C4099; codegen stays 82.27%, 69/72, with 8 clean
  masked operands.
- 2026-06-16 Golb type consolidation: the local projectile and game-rate views
  moved into `tools/match/include/golb.h` as `GolbShot` and
  `GolbProjectileGameView`. Codegen stays 82.27%, and this shares the
  projectile `velocity +0x24c`, `game +0x270`, `object_ref +0x274`, and
  `owner_player +0x278` lanes with the trail/impact/teardown helpers.
- 2026-06-16 position view cleanup: moving the `sprite->position` view down to
  the final copy site is score-neutral. The compiler still advances the sprite
  base before native does, but the source no longer exposes that view before it
  is needed.
- BN cross-check: this is the same word-index sprite emitter idiom as garbage
  smoke. The confirmed lanes are color at `0xb..0xe`, position at `0x12..0x14`,
  velocity at `0x15..0x17`, `size_start/size_end` at `0x18/0x19`, progress at
  `0x1a`, progress/lifetime steps at `0x1b/0x1d`, lifetime at `0x1c`, and
  gravity at `0x1e`.
- 2026-06-19 shared smoke tail pass: using a raw `float* sprite_words` view
  after the aggregate color copy for `size_start/size_end`, velocity, gravity,
  and position improves focused Wibo from 82.27% to 84.29%, moves the exact
  prefix from 34/72 to 43/72, and keeps 8 clean masked operands. The same idiom
  improves `spawn_garbage_smoke_particle`, confirming a shared smoke-emitter
  source-shape lead. The remaining gap is the native `lea velocity; add
  position-base` setup plus stack-staged velocity reloads.
- 2026-06-20 emitter-family retry: mutating the raw sprite cursor
  (`sprite_words += 18`) after forming the velocity pointer compiled
  identically. Interleaving the velocity stores around z scaling regressed to
  78.26%, so the accepted raw-tail shape remains.
- 2026-06-20 shared smoke-tail audit: focused Wibo still reports 84.29%,
  68/72 candidate instructions, 43/72 prefix, and eight clean masked operands.
  Deriving `out_position` from `out_velocity - 3`, spelling the same view as
  `Vector3* output_velocity` / `output_position`, adding a compact
  `SpriteMotionTail` overlay, and writing the reused `Color4f` lanes through a
  `float* color_words` view all compile back to the same direct `sprite + offset`
  tail. The overlay variant even schedules the gravity store before the delayed
  x-velocity store. Keep the raw float-lane source; the remaining gap is VC6
  choosing not to materialize native's `lea velocity; add position-base` cursor
  pair or the separate x-velocity stack spill.
- 2026-06-21 owner-header cleanup: `GolbShot::game` is now promoted to the
  shared `SubgameRuntime*`, so this scratch includes `subgame_runtime.h` before
  reading `subgame_rate`. Focused Wibo remains pinned at 84.29%, 68/72
  candidate instructions, 43/72 prefix, and eight clean masked operands.

Keep pinned unless a new source idiom explains the delayed sprite-base advance.
