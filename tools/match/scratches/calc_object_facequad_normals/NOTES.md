# calc_object_facequad_normals

First source-shaped scratch for `calc_object_facequad_normals @ 0x42fcb0`.

This is the full object normal rebuild used by object build and animation
refresh paths. It extends the lighter `calc_object_facequad_normals_simple`
shape with per-vertex normal accumulation:

- calls `request_object_facequad_normals` to ensure both `vertex_normals` and
  `facequad_normals` exist;
- allocates a temporary `Normal Tally` float array sized to `vertex_count`;
- zeros that tally with the native `memset`/rep-store pattern;
- walks each 0x30-byte facequad and writes two 12-byte face normals into the
  `Object::facequad_normals` pair stream;
- for four-index quads, accumulates the second face normal into all four
  vertex-normal slots with weight `1.0f`;
- accumulates the first face normal into all four vertex-normal slots with
  weight `2.0999999f`;
- reports `"Invalid Face Vertex Index"` when any face index is greater than
  `vertex_count`;
- divides each vertex normal by its tally, normalizes it, then inverts it;
- frees the temporary tally buffer.

Focused matcher result: 17.13%, 392 candidate instructions versus 437 target
instructions, with 11 clean masked operands and 1 masked constant mismatch from
the current low-similarity accumulation alignment.

The current scratch is intentionally relationship-first. The largest residual
is stack/register ownership: native reserves a 0x68-byte frame, keeps `this` in
`esi`, the tally buffer in `ebx`, face offset in `edi`, and normal offset in
`ebp`; this source compiles through a tighter 0x44-byte frame and different
nonvolatile roles. The repeated vertex-normal accumulation is semantically
correct but not yet shaped to native's repeated raw-offset stores.
