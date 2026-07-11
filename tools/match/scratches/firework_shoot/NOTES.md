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
- 2026-06-20 larger-chunk audit: naming the final X RNG result as an
  `int velocity_x_seed`, then storing `depth_offset` before scaling it, matches
  the IDA ordering but is codegen-neutral at 94.17%. VC6 still advances the
  sprite base to `position` before the final multiply. Keep the shorter source
  until a form delays that base advance without changing the aggregate
  velocity copy.
- 2026-06-20 continuation audit: focused Wibo still reports 94.17%, 103/103
  instructions, 78/103 prefix, and 21 clean masked operands. Explicit
  x/y/z position stores without the mid-copy decrement also regress to 59.51%
  by changing saved-register ownership. Narrowing the aggregate position-copy
  pointer with an inner block, copying through a `Vector3 source_position`
  local, spelling the loop decrement as a separate `--remaining; while
  (remaining != 0)`, and viewing the input as `float*` with an aggregate cast
  are all codegen-neutral and leave the same early `add esi, 0x48` schedule.
  Keep this scratch source-shaped at 94.17%; the remaining tail is a local
  lifetime/scheduling residual unless new original-source evidence appears.
- 2026-06-20 presentation-helper audit: focused Wibo still reports 94.17%,
  103/103 instructions, 78/103 prefix, and 21 clean masked operands. The
  residual tail remains only scheduling around the final random-x multiply,
  aggregate velocity copy, and position-base advance: native completes the
  multiply and velocity stores before `add esi, 0x48`, while VC6 hoists the
  position base advance. Do not rewrite this into manual lane stores; previous
  lane-level position/velocity copies regress badly and lose the aggregate
  source shape.

## 2026-07-11 receiver ownership

The Android symbol and its only caller identify this as
`cRFireWork::Shoot`, not a free `__stdcall` helper. Windows likewise loads
`ecx = Player + 0x1d0` before passing the four explicit arguments and returns
with `ret 0x10`; the body simply does not consume its receiver. Shared source
now models the one-byte empty `FireworkController` embedded at
`Player::firework +0x1d0`, and this scratch uses the corresponding thiscall
method definition.

The signature correction is codegen-neutral inside the callee: focused Wibo
remains `94.17%`, `103/103`, prefix `78/103`, with all `21` masked operands
clean. It recovers real ownership and fixes the caller's calling convention
without inventing controller state.
