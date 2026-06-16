# build_object_texture_group_buffers

Structure-first scratch for the object texture-group buffer builder at
`0x413d50`.

Current Wibo result: 20.20%, 330/373 candidate/target instruction shape,
prefix 0/373, masked operands 21 ok, 0 unresolved, 0 mismatch.

Recovered relationships:

- Called only by `build_all_objects`.
- If `Object +0x2c` vertex count is zero, native clears `+0xcc/+0xd0/+0xd4`,
  `+0xc0`, and `+0xc8`, then returns.
- Non-empty objects set `flags |= 0x80000`, which is the same tint-rewrite gate
  consumed by exact `set_object_color`.
- Allocates three per-texture-group arrays:
  - `Object +0xcc`: index-buffer start offset per texture group.
  - `Object +0xd0`: texture reference per texture group.
  - `Object +0xd4`: primitive count per texture group.
- `Object +0x6c` entries are cumulative facequad end indices, confirmed by
  `calc_object_texture_groups`; they are not per-group counts.
- `g_object_grouped_vertex_scratch` (`data_5031c4`) points at 0x1c-byte
  temporary vertices filled by `get_or_append_object_texture_group_vertex`.
- `g_object_grouped_vertex_cursor` (`data_5031bc`) is reset here, incremented
  by the append helper, then copied into `Object +0xc4`.
- `Object +0xc0` receives the D3D vertex-buffer wrapper and `Object +0xc8`
  receives the D3D index-buffer wrapper.
- Facequad flag `0x80` selects the three-index form; otherwise native emits six
  indices by reusing indices 0 and 2 plus the fourth corner.
- Toon/secondary index buffer allocation is gated by `flags & 0x4000`
  (`test ah, 0x40`), not by `flags & 0x40`.
- The vertex-buffer factory is the existing `g_direct3d_renderer` object at
  `0x4f7458` under a scratch-local factory view. The index-buffer factory is
  the neighboring object at `0x5000fc`.

Expected residuals:

- This source is intentionally relationship-first. The native function has
  hand-shaped nested loops with shared locals for face cursor, index cursor,
  primitive count, and index-output pointers. The scratch uses clearer loops to
  preserve ownership and field evidence before any source-shape golfing.
