# set_matrix_z_direction @ 0x44d410

Exact match: 100.00%, 57/57 instructions.

Normalizes a requested z direction into the forward basis, derives a horizontal
right vector with the native vertical-direction fallback, normalizes it, then
rebuilds the up vector via exact `cross_vectors`.

The source keeps a persistent `basis_up` pointer so VC6 preserves the native
saved-`edi` call shape for the final cross product.

2026-07-14 ownership closure: iOS and Android preserve
`tMatrix::SetZDir(tVector const&)`. The shared source and all owned callers now
use `const Vector3&`; the exact helper remains 57/57 instructions with six
clean operands, and exact/partial callers retain their baselines.
