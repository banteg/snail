# render_object_toon

Relationship-first scratch for the private toon/outline render helper at
`0x4123e0`.

Current Wibo result: exact, 219/219 instructions and full prefix, with 31
clean masked operands and no unresolved or mismatched operands.

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
- `ObjectToonEdge` lives in `object_render_types.h`; edge `+0x04/+0x08` are
  full 32-bit vertex indices, truncated only when written to the 16-bit index
  buffer. Edge `+0x0c/+0x10` are normal indices into the facequad-normal array
  at `Object +0x60`.
- If edge flag bit `1` is set, the edge is emitted unconditionally. If clear,
  native computes two dot products against the edge normals and emits when
  their product is below `0.00999999978f`.
- Binds sprite texture id `0x5d` through the global `SpriteManager` owner and
  draws `DrawIndexedPrimitive` primitive type `2` through a cached global D3D
  device with `Object +0xc4` grouped vertex count.

Exact source-shape recovery:

- the camera delta and per-edge vertex delta each have a source value followed
  by the copied value consumed by the matrix/vector operation;
- the loop counter is stack-resident, while `ebp` owns the 0x24-byte edge
  offset and the edge array is reloaded instead of cached;
- named normal A/B pointers preserve normal A across the first dot-product
  call, giving `edi` its native ownership;
- `emitted` is initialized before the index-buffer lock, so its zero value also
  supplies the lock offset and flags;
- the dot-product result is a float local, and the member-style call returns a
  float at this callsite, matching the native dword spill and comparison.
