# multiply_vector_by_matrix_copy @ 0x44cac0

Exact match: 100.00%, 49/49 instructions.

Out-of-place affine vector transform. Native initializes a stack `Vec3` result
from `this`, overwrites each component from the matrix basis plus translation,
then copies that aggregate into the caller-provided output.

2026-06-20 ABI note: the exact out-of-place transform signature now lives on
`Vector3` in `tools/match/include/vector3.h`, and the three local math/Bod
scratches use the shared header type instead of scratch-local `Vec3` structs.
`apply_bod_position` and this helper stayed exact, `multiply_vector_by_matrix`
stayed at its known 85.00% scheduling-only partial, and the remaining
`Vector3` type debt is isolated to the header-only rotate overload split.
