# apply_bod_position @ 0x42f680

Exact match with `END=0x42f6d9`; the default manifest extent also includes
seven nops plus an adjacent uncurated thunk at `0x42f6e0`.

Semantics:

- iterates every vertex in the attached `Object` (`object + 0x2c`
  count, `object + 0x38` vertex array);
- transforms each vertex through exact `multiply_vector_by_matrix_copy`;
- writes the transformed x/y/z lanes back into the same vertex slot;
- reloads `object` for the loop guard, matching native owner lifetime.

Source-shape note: the direct member-call expression is required. Introducing a
named `source` pointer makes VC6 compute the vertex `this` pointer before the
stack scratch argument and regresses the loop call setup.

The transformed lanes can be copied with ordinary `destination->x/y/z` field
assignments. VC6 still emits dword moves for the float copy, so no `*(int*)&`
bit-punning is needed here.

2026-07-14 ownership pass: the exact function now uses the shared `Object`
owner directly for `vertex_count` and `vertices`; the scratch-local
`ObjectGeometry` prefix overlay was redundant. The result remains 39/39 exact
with its matrix-helper operand clean.

2026-07-14 operator ownership: the callee definition is now the real
value-returning matrix `operator*`, but this exact consumer retains its explicit
hidden-sret compatibility call. Natural named-value and const-reference
spellings both make VC6 stop dereferencing the returned EAX pointer and regress
this loop to 76.92%, so they are rejected rather than normalized away.
