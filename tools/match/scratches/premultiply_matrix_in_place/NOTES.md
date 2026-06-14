# premultiply_matrix_in_place @ 0x44d1e0

Exact match: 100.00%, 18/18 instructions.

Copies the destination matrix to a stack temporary, then dispatches the native
output-member `multiply_matrices(rhs, &saved_lhs)` call shape.
