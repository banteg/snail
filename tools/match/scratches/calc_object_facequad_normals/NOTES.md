# calc_object_facequad_normals

Ownership-recovered scratch for `calc_object_facequad_normals @ 0x42fcb0`.

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

2026-07-10 ownership recovery applies the exact value and alias shape proven by
`calc_object_facequad_normals_simple`:

- each vertex subtraction first owns a temporary `Vector3`, then copies into
  the persistent `lhs` or `rhs` cross-product operand;
- face and output-normal addresses are recomputed from their byte offsets
  instead of retained as long-lived pointers;
- quad normal construction/storage and quad accumulation are two independent
  flag checks, matching the native control flow;
- vertex-normal additions for all four face indices happen first, followed by
  all four tally increments, for both the `1.0f` quad contribution and the
  `2.0999999f` primary contribution;
- final inversion owns a returned/temporary vector value which is copied back,
  while the divide-only normal pointer ends before normalization;
- the same source counter is reset between face and vertex phases, and tally
  access remains the natural `normal_tally[index]` expression.

Focused Wibo rises from 17.13% (392/437, one masked mismatch) to 90.03%,
436/437 candidate/target instructions, prefix 27/437, and 22 clean masked
operands with no unresolved or mismatched operands. Native now agrees on the
0x68-byte frame, `this` in `esi`, tally allocation in `ebx`, and face offset in
`edi`.

The honest residual is VC6 allocation/encoding: it assigns the shared counter
and normal offset to the opposite two stack slots, chooses the counter rather
than the strength-reduced tally cursor for `ebp` in the final phase, and emits
equivalent base/index ordering for repeated `facequads + face_offset` SIB
operands. Explicit cursor, declaration-order, operand-order, and wider pointer
lifetime probes did not recover that tie and were not retained.

The iOS ARMv6 binary retains this owner as
`cRObject::CalcFaceQuadNormals()` in `RObject.o`; both Windows callers discard
EAX and consume the rebuilt normal arrays through the same `Object`. The
analysis headers and repeatable BN/IDA sync now use the source-shaped void
thiscall instead of a synthetic integer fastcall. This is an ownership/ABI
correction only and does not hide the 90.03% stack-allocation residual.
