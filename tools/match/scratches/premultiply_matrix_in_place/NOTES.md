# premultiply_matrix_in_place @ 0x44d1e0

Exact match: 100.00%, 18/18 instructions.

Copies the destination matrix to a stack temporary, then dispatches the native
output-member `multiply_matrices(lhs, saved_rhs)` call shape.

2026-07-14 return closure: the core leaves its second operand in EAX, which in
this wrapper is the address of the saved stack matrix. That pointer is invalid
after return and the sole caller discards it, proving the member is void. The
const-reference left operand and void definition preserve all 18 instructions
and the clean call operand.
