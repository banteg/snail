# multiply_matrix_in_place @ 0x44d1a0

Exact match: 100.00%, 18/18 instructions.

Copies the destination matrix to a stack temporary, then dispatches the native
output-member `multiply_matrices(&saved_lhs, rhs)` call shape.

The scratch pins `END=0x44d1cd` because the manifest gap includes the adjacent
uncurated thunk at `0x44d1d0`, which simply forwards to this helper.
