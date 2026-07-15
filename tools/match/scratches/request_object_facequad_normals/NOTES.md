# request_object_facequad_normals @ 0x42f800

Exact match.

Semantics:

- allocates `vertex_count * sizeof(Vector3)` bytes for accumulated vertex normals at
  `+0x44` when absent;
- allocates two `Vector3` normals per facequad at `+0x60` when absent;
- leaves existing buffers untouched and returns the facequad-normal buffer.

This completes the toon-normal allocation side of the object mesh helper group
alongside exact `request_object_vertices`, `request_object_vertex_colours`, and
`request_object_facequads`.

2026-07-14 allocation ownership: both banks now derive their extents from the
shared `Vector3` element type. Matching remains exact at 26/26 instructions
with all four operands clean.

2026-07-15 return ownership: both native branches leave the retained
`facequad_normals` bank in EAX, so the member now exposes the coherent
`Vector3*` result instead of erasing it to `void*`. The two Windows callers
discard that result and consume the same bank through `Object +0x60`; the
signature correction remains exact at 26/26 instructions with four clean
operands.
