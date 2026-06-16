# render_object_toon

Relationship-first scratch for the private toon/outline render helper at
`0x4123e0`.

Current Wibo result: 57.76%, 200/219 candidate/target instruction shape,
prefix 0/219, masked operands 28 ok, 0 unresolved, 0 mismatch.

Recovered relationships:

- Called only by `render_object`.
- The gate is `flags & 0x4000` (`test ah, 0x40`), not low bit `0x40`.
- Temporarily expands the perspective projection by using
  `near_z + 0.00400000019f` and `far_z + 30.0f`, then restores the original
  projection at exit.
- `g_render_camera_source_matrix` points at the active camera/source transform;
  toon subtracts object matrix position and rotates that vector into object
  space through exact `invert_matrix_in_place` and `rotate_vector_by_matrix`.
- Consumes `Object +0xd8` as the toon/secondary index-buffer wrapper created by
  `build_object_texture_group_buffers`.
- Uses `Object +0x70` edge count and `+0x74` 0x24-byte edge records, matching
  exact `request_object_edges`.
- Edge `+0x04/+0x08` are the two vertex indices written to the toon index
  buffer. Edge `+0x0c/+0x10` are normal indices into `Object +0x60`.
- If edge flag bit `1` is set, the edge is emitted unconditionally. If clear,
  native computes two dot products against the edge normals and emits when
  their product is below `0.00999999978f`.
- Binds sprite texture id `0x5d` and draws `DrawIndexedPrimitive` primitive type
  `2` with `Object +0xc4` grouped vertex count.

Expected residuals:

- The source keeps the edge loop clear. Native re-locks the toon index buffer
  for each edge, uses a large 0xb0-byte stack frame, and has delicate x87
  scheduling around the two dot products and projection reset.
