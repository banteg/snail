# rotate_matrix_world_y @ 0x44cec0

Exact match: 100.00%, 50/50 instructions.

Applies an in-place local-Y rotation by mixing the right and forward basis
vectors with the shared sine/cosine table helpers.

2026-07-14 owner correction: both mobile binaries export
`tMatrix::RotLocalY(float)`, consistent with the member mixing its receiver's
right/forward basis rows. The source now uses
`TransformMatrix::rotate_matrix_local_y`; the Windows dashboard name remains a
stable harness identity, and all 50 instructions remain exact.
