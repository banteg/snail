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
- explicit velocity/position output pointers are score-neutral, but match the
  decompiler's clearer source view and are kept.

Keep pinned unless a new source idiom explains the delayed sprite-base advance.
