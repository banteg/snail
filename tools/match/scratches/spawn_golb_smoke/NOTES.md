# Exact match — scaled Vector3 smoke velocity

`spawn_golb_smoke` now matches at 100.00%, 72/72 candidate and target
instructions, with a complete exact prefix and eight clean masked operands.

The scratch covers the recovered smoke producer behavior:

- allocate sprite id `128` for the owning player slot;
- set the smoke flag bit, clear progress lanes, and derive progress/lifetime
  steps from `game->subgame_rate`;
- copy white RGBA into the sprite color, seed scale `0.1f` by `0.5f`;
- scale the Golb velocity by `0.40000001f`, clear the gravity lane, and copy
  the caller position into the sprite.

The former residual was source shape rather than a semantic gap. The accepted
scaled-`Vector3` spelling and non-overlapping temporary scopes are documented
in the 2026-07-25 recovery below.

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
  `SpriteMotionTail` overlay, and writing the reused `tColour` lanes through a
  `float* color_words` view all compile back to the same direct `sprite + offset`
  tail. The overlay variant even schedules the gravity store before the delayed
  x-velocity store. Keep the raw float-lane source; the remaining gap is VC6
  choosing not to materialize native's `lea velocity; add position-base` cursor
  pair or the separate x-velocity stack spill.
- 2026-06-21 owner-header cleanup: `GolbShot::game` is now promoted to the
  shared `SubgameRuntime*`, so this scratch includes `subgame_runtime.h` before
  reading `subgame_rate`. Focused Wibo remains pinned at 84.29%, 68/72
  candidate instructions, 43/72 prefix, and eight clean masked operands.

This remained the pinned frontier until the scaled-vector owner recovery
below explained the delayed Sprite-base advance.

## 2026-07-16 analysis receiver and ABI replay

The shared Golb ownership replay now applies
`void __thiscall spawn_golb_smoke(GolbShot*, Vec3*)` in both Binary Ninja and
IDA. The Windows callers ignore EAX and the success path merely leaves the
copied position-z bits there, so the previous inferred float result was not an
owned contract. Replaying the void mutator also resolves `game`,
`owner_player`, and `velocity` through the complete `GolbShot` owner. Focused
matching remains honestly pinned at 84.29%, 68/72 instructions, with all eight
masked operands clean.

## 2026-07-23 shared Sprite owner lifetime replay

The allocation result is now a durable `Sprite*`, and the native register that
starts at `Sprite::position` is replayed as a byte cursor rather than BN's
overly narrow `Vec3*`. This lets the enclosing Sprite recover color, size,
velocity, gravity, and position fields without introducing a synthetic
motion-tail struct. Transactional preview rejected that overlay because it
only traded `__offset` for misleading nested `position.x` expressions. This
analysis-only clarification leaves the honest 84.29%, 68/72 frontier and all
eight clean masks unchanged.

## 2026-07-25 scaled-velocity owner recovery

Ghidra 12.1.2 independently decompiles Android's symbol-preserving
`cRSubGolb::Smoke(tVector)` as a side-effect-only Sprite producer: it scales
the three projectile velocity lanes by the same factor, clears gravity, and
copies the by-value position into the Sprite. The mobile optimizer emits those
stores directly, while Windows retains a three-lane stack value.

Modeling that value as `Vector3 smoke_velocity = velocity * 0.40000001f`
followed by the authored aggregate assignment recovers all four previously
missing Windows instructions and the exact split x/gravity/y/z store schedule.
Narrowing the preceding temporary color to its real source scope lets VC6
reuse the same 0x10-byte frame slot for the non-overlapping vector, matching
the native stack extent without padding or an artificial local.

Focused matching rises from 84.29% (68/72 instructions, prefix 43) to
**100.00%** (72/72 instructions and prefix), with all eight masked operands
clean. The smoke velocity and Sprite motion lanes now have semantic owners;
no register-directed spelling or synthetic constant was introduced.
