# set_object_color

Exact scratch for the object tint helper at `0x4141d0`.

Current Wibo result: 100.00%, 47/47 instructions, prefix 47/47, masked
operands 3 ok, 0 unresolved, 0 mismatch.

Recovered relationships:

- Called by `render_object`, `populate_runtime_track_cells_from_segments`, and
  the asset/world initialization loop.
- Packs the incoming `tColour` into a local `tColourSmall` through the same
  no-op constructor and `pack_color_rgba_u8` helper used by sprite rendering.
- `Object +0x10` flag `OBJECT_FLAG_RENDER_BUFFERS_READY` enables rewriting
  diffuse colours in the grouped render vertex stream.
- `Object +0xc0` is the render-buffer owner and `+0x08` inside it is the D3D
  vertex buffer, matching `refresh_object_vertex_buffer`.
- The diffuse write loop uses `Object +0xc4` as the grouped vertex count.
- The locked stream is the shared `ObjectRenderVertex` layout; the loop now
  writes `vertices[i].diffuse` instead of a raw `+0x0c` vertex offset and still
  matches byte-for-byte.

Corrected assumptions:

- The lock size is based on global `g_object_grouped_vertex_cursor`
  (`data_5031bc`), not directly on `Object +0xc4`. `build_object_texture_group_buffers`
  shows that this global is copied to `Object +0xc4` after group construction,
  so the two are related but not interchangeable at every callsite.

Cross-port ownership and ABI closure:

- Android names the packed owner `tColourSmall`, with the same BGRA byte order.
- Android's corresponding `G0SetColour(tColourSmall*)` is void, and all 26
  Windows callsites discard `eax`.
- The recovered Windows helper is therefore void. Native still naturally
  leaves either the pack helper's pointer or the D3D `Unlock` result in `eax`;
  removing the synthetic result variable and returns is codegen-neutral at
  47/47 instructions with all three operands clean.
