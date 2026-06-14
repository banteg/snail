# apply_bod_position @ 0x42f680

Exact match with `END=0x42f6d9`; the default manifest extent also includes
seven nops plus an adjacent uncurated thunk at `0x42f6e0`.

Semantics:

- iterates every vertex in the attached object geometry (`object + 0x2c`
  count, `object + 0x38` vertex array);
- transforms each vertex through exact `multiply_vector_by_matrix_copy`;
- writes the transformed x/y/z lanes back into the same vertex slot;
- reloads `object` for the loop guard, matching native owner lifetime.

Source-shape note: the direct member-call expression is required. Introducing a
named `source` pointer makes VC6 compute the vertex `this` pointer before the
stack scratch argument and regresses the loop call setup.
