# multiply_matrix_assign @ 0x44d1a0

Exact match: 100.00%, 18/18 instructions.

Copies the destination matrix to a stack temporary, then dispatches the native
output-member `multiply_matrices(saved_lhs, rhs)` call shape.

The scratch pins `END=0x44d1cd` so the adjacent `multiply_matrix` member at
`0x44d1d0` stays out of the exact helper extent.

## 2026-07-24 operator ownership correction

Android exports adjacent `tMatrix::operator*=(const tMatrix&)` and
`tMatrix::Multiply(const tMatrix&)` symbols. Its `Multiply` entry is a direct
branch to `operator*=`, whose full body snapshots the receiver and calls the
two-reference multiply core. Windows has the same split: this 18-instruction
body is the operator, while `0x44d1d0` is the four-instruction `Multiply`
forwarder. iOS independently exports both authored names, and its LoopBow
constructor calls `Multiply` at the corresponding two composition sites.

The Windows body does not restore the receiver in EAX after the core call, so
the authored operator is `void`, not the conventional reference-returning
shape. Defining `void tMatrix::operator*=(const TransformMatrix&)`
remains exact at 18/18 with its core-call operand clean.
