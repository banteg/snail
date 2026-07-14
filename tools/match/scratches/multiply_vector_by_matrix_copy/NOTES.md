# multiply_vector_by_matrix_copy @ 0x44cac0

Exact match: 100.00%, 49/49 instructions.

This is the value-returning
`Vector3::operator*(const TransformMatrix&) const` affine transform retained by
Android and iOS. Native initializes a stack result from `this`, overwrites each
component from the matrix basis plus translation, then copies that aggregate to
the hidden VC6 output pointer.

2026-06-20 ABI note: the exact out-of-place transform signature now lives on
`Vector3` in `tools/match/include/vector3.h`, and the three local math/Bod
scratches use the shared header type instead of scratch-local `Vec3` structs.
`apply_bod_position` and this helper stayed exact, `multiply_vector_by_matrix`
stayed at its known 85.00% scheduling-only partial, and the remaining
`Vector3` type debt is isolated to the header-only rotate overload split.

2026-07-14 operator ownership: expressing the definition as the real
value-returning operator preserves all 49 target instructions. The exact
`apply_bod_position` consumer continues to use a documented explicit-sret ABI
view: both a named value and a const reference to the temporary make VC6 ignore
the returned EAX pointer and regress that caller from 100% to 76.92%. No caller
code is claimed from those rejected spellings.
