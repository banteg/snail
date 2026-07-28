# set_object_color

Exact scratch for the object tint helper at `0x4141d0`.

Current Wibo result: 100.00%, 47/47 instructions, prefix 47/47, masked
operands 3 ok, 0 unresolved, 0 mismatch.

Recovered relationships:

- Called by `render_object`, `populate_runtime_track_cells_from_segments`, and
  the asset/world initialization loop.
- Packs the incoming `tColour` into a local `tColourSmall` through the same
  no-op constructor and authored assignment operator used by sprite rendering.
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

## 2026-07-23 locked diffuse stream ownership

Binary Ninja now preserves the D3D lock output as the borrowed
`ObjectRenderVertex*` stream shared with `refresh_object_vertex_buffer`.
The native loop's `0x18`-byte strength-reduced cursor remains an integer, while
the completed store resolves through `locked_vertices->diffuse`; the previous
`void* data + 0x0c` presentation is gone. The replay verifies the canonical
24-byte render vertex and retained render-buffer chain before mutation.

Preview/apply readback verified the stack output, integer byte cursor, and
post-lock stream reload. A second run skipped all three as already current.
No matcher source changed: focused output remains exact at `100.00%`, `47/47`
instructions, prefix `47/47`, with all three operands clean.
