# multiply_vector_by_matrix_copy @ 0x44cac0

Exact match: 100.00%, 49/49 instructions.

Out-of-place affine vector transform. Native initializes a stack `Vec3` result
from `this`, overwrites each component from the matrix basis plus translation,
then copies that aggregate into the caller-provided output.
