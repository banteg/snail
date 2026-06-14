# rotate_vector_by_matrix @ 0x44cc20

Exact match: 100.00%, 38/38 instructions.

In-place vector rotation through the 3x3 matrix basis only, leaving translation
out. The native source shape copies `this` to a stack `Vec3` before overwriting
the destination vector.
