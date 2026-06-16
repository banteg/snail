# Source-shaped pinned match

`spawn_golb_smoke` currently matches at 82.27%, 69 candidate instructions versus
72 target instructions, with a 34/72 exact prefix.

The scratch covers the recovered smoke producer behavior:

- allocate sprite id `128` for the owning player slot;
- set the smoke flag bit, clear progress lanes, and derive progress/lifetime
  steps from `game->subgame_rate`;
- copy white RGBA into the sprite color, seed scale `0.1f` by `0.5f`;
- scale the Golb velocity by `0.40000001f`, clear the gravity lane, and copy
  the caller position into the sprite.

The remaining residual is source-shape/codegen, not a known semantic gap.
Native keeps the sprite base in `esi` through the color and scale stores, then
creates the position-base form later. The current source moves the position-base
form earlier, so the same fields are reached through shifted offsets. The final
velocity x/y/z x87 staging also differs, while the values and writes are covered.

Rejected source-shaped probes:

- explicit RGBA field copies through an `out_color` pointer regressed the score
  to 65.71% by changing the color copy and velocity x87 schedule;
- separate `velocity_x/velocity_y/velocity_z` scalar locals plus an earlier
  `out_velocity` pointer grew the frame to `0x14`, reordered the x87 stack, and
  regressed the score to 61.87%;
- explicit velocity/position output pointers are score-neutral, but match the
  decompiler's clearer source view and are kept.
- 2026-06-16 cleanup: the local `Game` view is now a `class` to match
  `player.h` and remove C4099; codegen stays 82.27%, 69/72, with 8 clean
  masked operands.
- BN cross-check: this is the same word-index sprite emitter idiom as garbage
  smoke. The confirmed lanes are color at `0xb..0xe`, position at `0x12..0x14`,
  velocity at `0x15..0x17`, `size_start/size_end` at `0x18/0x19`, progress at
  `0x1a`, progress/lifetime steps at `0x1b/0x1d`, lifetime at `0x1c`, and
  gravity at `0x1e`.

Keep pinned unless a new source idiom explains the delayed sprite-base advance.
