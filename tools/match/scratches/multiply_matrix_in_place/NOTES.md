# multiply_matrix_in_place @ 0x44d1a0

Exact match: 100.00%, 18/18 instructions.

Copies the destination matrix to a stack temporary, then dispatches the native
output-member `multiply_matrices(saved_lhs, rhs)` call shape.

The scratch pins `END=0x44d1cd` so the adjacent
`multiply_matrix_in_place_forward_thunk` at `0x44d1d0` stays out of the exact
helper extent.

2026-07-14 owner recovery: iOS and Android both export the one-argument member
as `tMatrix::Multiply(const tMatrix&)`. The Windows body now defines
`void TransformMatrix::multiply_matrix(const TransformMatrix&)`, snapshots its
receiver, and calls the recovered two-reference core. Native only inherits the
core's incidental rhs value in EAX and every direct caller discards it, so the
old pointer return was not a real contract. The void/reference spelling and all
18 instructions remain exact.
