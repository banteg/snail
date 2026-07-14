# Vector3::normalize_vector_from_source @ 0x44cd20

Copies the source vector into `this` and tail-calls the recovered
`Vector3::normalize_vector()` method. Both the copy-and-normalize wrapper and
its callee remain exact, preserving the authored `tVector` ownership visible in
the Android symbols.

2026-07-14 const-reference pass: Android retains the overload as
`tVector::Normalize(const tVector&)`; Windows' pushed source pointer is the ABI
form of that reference, not nullable ownership. Direct source assignment and
the `set_matrix_z_direction` caller stay exact at 12/12 and 57/57.
