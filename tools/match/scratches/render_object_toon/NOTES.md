# render_object_toon

Relationship-first scratch for the private toon/outline render helper at
`0x4123e0`.

Current Wibo result: exact, 219/219 instructions and full prefix, with 31
clean masked operands and no unresolved or mismatched operands.

Recovered relationships:

- Called only by `render_object`.
- The gate is `OBJECT_FLAG_TOON_ENABLED` (`flags & 0x4000`, emitted as
  `test ah, 0x40`), not low bit `0x40`.
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
- If `OBJECT_TOON_EDGE_FLAG_BOUNDARY` is set, the edge is emitted
  unconditionally. A shared edge instead uses two dot products against its
  face normals and emits when their product is below `0.00999999978f`.
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

2026-07-11 device-owner closure: toon rendering now uses the same
IDirect3DDevice8 type as the camera, object, sprite, loading, and texture paths.
The indexed draw and index/stream binding slots remain exact; focused matching
stays 219/219 with all 31 operands clean.

2026-07-12 vector callsite consolidation: the independently proved
float-returning `Vector3::dot_vector` declaration replaces the scratch-local
`ToonVector3` duplicate. Both per-edge delta values, both face-normal operands,
and both dot calls now use the shared `Vector3` owner directly. Focused matching
remains proof-grade at 219/219 with all 31 operands clean.

2026-07-14 stream extent ownership: the render stream stride now comes from
`sizeof(ObjectRenderVertex)`, and the temporary toon index lock size comes
from `sizeof(unsigned short)`. Both substitutions are byte-identical at
219/219 instructions with all 31 operands clean.

2026-07-16 render-pipeline state ownership: toon rendering now consumes the
same camera source, projection parameters, and render counters as the exact
camera/object paths. Focused output remains exact at 219/219 instructions with
all 31 operands clean.

2026-07-18 tracked replay refresh: rebuilding the topology consumer after the
edge-bank sync exposes the already-proven
`get_sprite_texture(&g_sprite_manager, 0x5d)` owner in both generated
artifacts. This is an artifact freshness fix; the scratch remains exact at
219/219 with all 31 operands clean.

2026-07-23 downstream edge ownership: the guarded edge-builder replay now
continues into this consumer. The index-buffer `Lock` output is a borrowed
`uint16_t*`, `edge_index` and the 0x24-stride `edge_byte_offset` remain
independent integers, and only the post-addition borrow is typed
`ObjectToonEdge*`. The same replay records the projection, view vector,
per-edge delta, normal A/B, source vertex, and reloaded index-buffer
lifetimes. No matcher source changed; focused output remains exact at 219/219
instructions with all 31 operands clean.

## 2026-07-26 mobile G0 owner and void ABI

Android and iOS retain the exact two-argument owner as
`G0RenderToon(cRObject*, tMatrix*)`. Their OpenGL bodies independently preserve
the active `G0Camera` subtraction, matrix inversion and object-space rotation,
boundary-edge flag, paired face-normal dot products, `0.01` silhouette
threshold, and line-index submission. Backend buffers and draw calls differ,
but the source owner and edge topology do not.

The sole Windows caller at `0x412930` adjusts the stack and immediately tears
down its frame without consuming EAX. Both mobile bodies are void. Replacing
the synthetic early flags and final SetTransform results with a natural void
body remains exact at 219/219 instructions with all 31 operands clean.
