# render_object

Relationship-first scratch for the object renderer at `0x4126c0`.

Current Wibo result: 69.72%, 197/196 candidate/target instruction shape,
prefix 8/196, masked operands 21 ok, 0 unresolved, 0 mismatch.

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
- `flags & 0x80` enables a texture transform: argument 3 is stored into
  `g_object_texture_transform_matrix.basis_forward.x`, and `1.0f - argument4`
  into `.basis_forward.y`, then Direct3D transform state `0x10` and
  texture-stage state `0x18 = 2` are applied.
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

Expected residuals:

- The source is intentionally clear rather than native-shaped. Expected
  residuals are pass-filter branch layout, stack copying of the `Color4f`
  argument before `set_object_color`, and per-call D3D device reload scheduling.

## Type consolidation (2026-06-17)

`ObjectFaceQuad`, `ObjectIndexBuffer`, `ObjectIndexBufferResource`, and the
`RenderObjectDeviceVtbl` slot window now live in `object_render_types.h`.
Focused checks for `render_object`, `render_object_toon`,
`refresh_object_vertex_buffer`, `calc_object_texture_groups`, and
`build_object_texture_group_buffers` keep their previous match ratios. The
full `Object` views remain scratch-local because allocation, build, and render
paths still expose different validated windows into the larger object layout.
