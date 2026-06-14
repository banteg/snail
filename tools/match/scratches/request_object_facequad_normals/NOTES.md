# request_object_facequad_normals @ 0x42f800

Exact match.

Semantics:

- allocates `vertex_count * 0xc` bytes for accumulated vertex normals at
  `+0x44` when absent;
- allocates `facequad_count * 0x18` bytes for facequad-normal pairs at `+0x60`
  when absent;
- leaves existing buffers untouched and returns the facequad-normal buffer.

This completes the toon-normal allocation side of the object mesh helper group
alongside exact `request_object_vertices`, `request_object_vertex_colours`, and
`request_object_facequads`.
