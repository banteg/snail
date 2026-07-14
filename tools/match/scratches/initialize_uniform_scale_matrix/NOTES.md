# initialize_uniform_scale_matrix @ 0x44cde0

Exact match: 100.00%, 21/21 instructions.

Initializes a full 4x4 transform matrix to a uniform scale on the x/y/z diagonal,
zeroes off-diagonal and translation lanes, and writes `position.w = 1.0f`.

Android preserves this exact ownership as both emitted single-float constructor
symbols for `tMatrix::tMatrix(float)`. Expressing the Windows body as the real
`TransformMatrix(float)` constructor remains byte-identical at 21/21
instructions. The `mov eax, ecx` result is the VC6 constructor ABI, not a
pointer-returning `Scale` method; Android and iOS retain a separate mutating
`tMatrix::Scale(float)` function.
