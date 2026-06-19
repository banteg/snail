# firework_shoot @ 0x441dd0

Spawns a burst of small firework sprites at a supplied world position. The only
known callsite is `handle_subgoldy_collisions`, which passes a burst position,
player slot, texture id, and particle count.

Recovered behavior:

- gates on `byte_4df934 & 0x10`;
- allocates `count` sprites through `g_sprite_manager`;
- uses owner and texture id from the caller, with both alternate textures set
  to `-1`;
- arms draw mode 10, render flags `0x802`, progress/lifetime fields, and a
  large corner scale;
- randomizes duration, red/yellow tint, and velocity;
- copies the supplied position into each spawned sprite.

This also identifies `0x44dbd0` as `Color4f::set_color_rgb(float,float,float)`,
a three-channel setter used here after randomizing the red component.

Source-shape notes:

- 2026-06-20 z/y temporary staging: focused Wibo improves from 78.22% to
  94.17% (103/103 instructions, prefix 78/103, 21 clean masked operands).
  Keeping a real `Vector3 velocity` local preserves the native 0x10-byte stack
  frame, while staging the first two random components as `velocity_z` and
  `velocity_y` lets VC6 reuse the now-dead caller argument slots before copying
  them into the vector local.
- The remaining body mismatch is scheduling: native finishes the final x
  multiply and all three velocity stores before advancing the sprite base to
  `position`; the scratch advances that base immediately before the multiply.

Rejected source-shape probes:

- Scalar `random_x/y/z` locals compiled smaller and lost the native prologue.
- Changing the final position copy from `Vector3* out_position` to direct
  aggregate assignment was codegen-neutral at 94.17%.
- Manual x/y/z position stores with an explicit mid-copy decrement regressed to
  59.51% by changing saved-register ownership.
- Explicit `out_velocity->x/y/z` field stores collapsed the stack frame and
  regressed to 62.31%; keep the aggregate `sprite->velocity = velocity`.
- Naming only the final random X component as `velocity_x` is codegen-neutral
  at 94.17% and leaves the early `sprite + 0x48` schedule unchanged.
- Spelling the velocity destination as an aggregate `Vector3* out_velocity`
  regresses to 92.23% by moving the depth-offset store before the second
  temporary spill; keep the direct aggregate assignment.
- Applying the shared smoke-emitter raw float-lane tail is a hard regression
  to 46.46% here: it collapses the native stack/register model and direct-stores
  the velocity lanes instead of preserving the typed aggregate copy.
- A `Sprite* position_sprite` alias for the final position copy is codegen-neutral
  at 94.17%, so keep the clearer `Vector3* out_position` spelling.
