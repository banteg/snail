# premultiply_matrix_in_place @ 0x44d1e0

Exact match: 100.00%, 18/18 instructions.

Copies the destination matrix to a stack temporary, then dispatches the native
output-member `multiply_matrices(lhs, saved_rhs)` call shape.

2026-07-14 return closure: the core leaves its second operand in EAX, which in
this wrapper is the address of the saved stack matrix. That pointer is invalid
after return and the sole caller discards it, proving the member is void. The
const-reference left operand and void definition preserve all 18 instructions
and the clean call operand.

2026-07-27 mobile owner recovery: Android retains the standalone authored
symbol `tMatrix::PreMultiply(tMatrix const&)` in `RMaths.o`. Its four-byte
entry veneer resolves to the same source body as Windows: snapshot all 16
receiver words, then call the two-input `Multiply` core with the supplied left
operand and saved receiver as the right operand. This closes the Windows
member name without transferring mobile layout or inventing an iOS mapping;
iOS has no standalone `PreMultiply` export. The Windows scratch remains exact
at 18/18 instructions.
