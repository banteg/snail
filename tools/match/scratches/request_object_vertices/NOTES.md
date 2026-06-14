# request_object_vertices @ 0x42f710

Exact match.

Semantics:

- rejects counts above `0x10000` with `"Too many Vertices"`;
- warns and frees the old vertex buffer when a nonzero existing allocation is
  too small;
- allocates `vertex_count * 0xc` bytes at `+0x38`;
- stores the count at `+0x2c`;
- immediately requests the matching vertex-colour buffer through exact
  `request_object_vertex_colours`.
