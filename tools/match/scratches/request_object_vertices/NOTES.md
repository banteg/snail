# request_object_vertices @ 0x42f710

Exact match.

Semantics:

- rejects counts above `0x10000` with `"Too many Vertices"`;
- warns and frees the old vertex buffer when a nonzero existing allocation is
  too small;
- allocates `vertex_count * sizeof(Vector3)` bytes at `+0x38`;
- stores the count at `+0x2c`;
- immediately requests the matching vertex-colour buffer through exact
  `request_object_vertex_colours`.

2026-07-14 allocation ownership: the complete `Vector3` type now supplies the
vertex stride. Matching remains exact at 37/37 instructions with all eight
operands clean.

2026-07-15 Binary Ninja replay: the live prototype and tracked artifact now
retain the canonical `Object* object` receiver instead of the obsolete
path-strip prefix. Matching remains exact.
