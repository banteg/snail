# set_object_color

Exact scratch for the object tint helper at `0x4141d0`.

Current Wibo result: 100.00%, 47/47 instructions, prefix 47/47, masked
operands 3 ok, 0 unresolved, 0 mismatch.

Recovered relationships:

- Called by `render_object`, `populate_runtime_track_cells_from_segments`, and
  the asset/world initialization loop.
- Packs the incoming `Color4f` into a local `ColorBGRA8` through the same
  no-op constructor and `pack_color_rgba_u8` helper used by sprite rendering.
- `Object +0x10` flag `0x80000` enables rewriting diffuse colours in the
  grouped render vertex stream.
- `Object +0xc0` is the render-buffer owner and `+0x08` inside it is the D3D
  vertex buffer, matching `refresh_object_vertex_buffer`.
- The diffuse write loop uses `Object +0xc4` as the grouped vertex count.

Corrected assumptions:

- The lock size is based on global `g_object_grouped_vertex_cursor`
  (`data_5031bc`), not directly on `Object +0xc4`. `build_object_texture_group_buffers`
  shows that this global is copied to `Object +0xc4` after group construction,
  so the two are related but not interchangeable at every callsite.

Expected residuals:

- None for the scratch. Keep the return shape: if the tint rewrite path runs,
  native leaves the D3D vertex-buffer `Unlock` result in `eax`; only the
  no-update path returns the packed-color pointer.
