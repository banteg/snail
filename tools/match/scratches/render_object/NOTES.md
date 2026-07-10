# render_object

Relationship-first scratch for the object renderer at `0x4126c0`.

Current Wibo result: exact, 196/196 instructions and full prefix, with 25
clean masked operands and no unresolved or mismatched operands.

Recovered relationships:

- Called by `render_game_frame` in the world pass and the post-sprite replay
  pass.
- `render_game_frame` passes `BodBase::is_bod_after_sprites()` into this
  argument in both the immediate BOD pass and the staged post-sprite replay
  pass. `render_object` then combines that value with the global
  `g_object_render_pass_filter` and texture flag `0x10000` to choose which
  texture groups are drawn in each boundary pass.
- `render_camera` is the producer for `g_object_render_pass_filter`: BN shows
  its ninth argument stored to `data_503260`. `render_game_frame` calls it with
  `post_sprite_pass=0` for the normal world/sprite/text pass and
  `post_sprite_pass=1` immediately before replaying the staged post-sprite BOD
  stack.
- Early exit requires `flags & 0x80000`, rejects `flags & 0x40000`, and rejects
  zero `Object +0x2c` vertex count.
- Always calls `refresh_object_vertex_buffer` before setting the world transform
  when those gates pass.
- `flags & 0x100000` controls the cull-mode argument through exact
  `set_cull_mode`.
- Iterates `Object +0x64` texture groups and consumes the builder-owned arrays:
  `+0xcc` index starts, `+0xd0` texture refs, and `+0xd4` primitive counts.
- `flags & 8` selects `Object +0x18` as an override texture ref; otherwise the
  group texture ref is bound.
- `flags & 0x80` enables a texture transform: float texture-U argument 3 is
  stored into `g_object_texture_transform_matrix.basis_forward.x`, and
  `1.0f - argument4` into `.basis_forward.y`, then Direct3D transform state
  `0x10` and texture-stage state `0x18 = 2` are applied.
- Alpha/blend path calls `set_blend_mode(Object +0x14)` and, for
  `flags & 0x50`, clears bit `0x40` before exact `set_object_color`.
- Draw path binds `Object +0xc0` vertex buffer, shader `0x142`, `Object +0xc8`
  index buffer, then `DrawIndexedPrimitive(4, 0, Object +0xc4, +0xcc[i],
  +0xd4[i])`.
- Corrected D3D device vtable window: `SetStreamSource` is `+0x14c`, there is
  another slot at `+0x150`, and `SetIndices` is `+0x154`.
- Updates `g_render_triangle_count` by primitive count and increments
  `g_draw_primitive_call_count`.
- Tail-calls/calls private `render_object_toon` after all groups are processed.

## Type consolidation (2026-06-17)

`ObjectFaceQuad`, `ObjectIndexBuffer`, `ObjectIndexBufferResource`, and the
`RenderObjectDeviceVtbl` slot window now live in `object_render_types.h`.
Focused checks for `render_object`, `render_object_toon`,
`refresh_object_vertex_buffer`, `calc_object_texture_groups`, and
`build_object_texture_group_buffers` keep their previous match ratios. The
full `Object` views remain scratch-local because allocation, build, and render
paths still expose different validated windows into the larger object layout.

## Shared owner closure (2026-07-10)

The allocation, load, animation, build, refresh, and render paths now use one
shared `Object` layout; the earlier scratch-local qualification above is
superseded. The live Binary Ninja prototype now types the borrowed world
`TransformMatrix*` and `Color4f*` instead of `void*` / `int32_t*`, while the
object itself retains every grouped buffer and per-texture-group array consumed
here.

The native single-result early-exit shape also clarifies behavior: an enabled
object with zero vertices returns zero, while the disabled gates retain the
flags value. The render-pass filter now follows the exact two boundary cases,
and each group texture ref is borrowed at its use sites instead of being given
a false long-lived local owner. Together these changes raise focused Wibo to
80.31%, 195/196, prefix 39/196, with all 23 masked operands clean. The first
residual is honest register ownership: native keeps `after_sprites` in `bl` and
the color pointer in `edi`, while the candidate starts the loop with color in
`ebx` and texture-scroll bits in `edi`; later D3D transform scheduling remains
the other visible difference.

## Texture coordinate ownership closure (2026-07-10)

Cross-port `G0RenderObject(cRObject*, tMatrix*, float, float, ...)` provenance
and native dword-copy codegen together show that argument 3 is a float
texture-U value, not opaque integer bits. Expressing the matrix assignment as
`basis_forward.x = texture_u` removes the false integer lifetime: VC6 leaves
texture-U in its stack argument slot, gives `bl` to `after_sprites`, and gives
`edi` to the borrowed color pointer. The pass-filter branches, float texture
transform, `Color4f` by-value copy, and D3D call scheduling then all align
naturally.

The same correction is propagated to `BodBase +0x1c` and every shared BOD view;
`+0x1c/+0x20` are now the paired texture-U/texture-V float render arguments.
Focused Wibo is 100.00%, 196/196 instructions and full prefix, with 25 clean
masked operands.
