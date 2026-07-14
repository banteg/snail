# multiply_vector_by_matrix @ 0x44cb90

Exact match: 100.00%, 40/40 instructions.

This is the Windows void `Vector3::operator*=(TransformMatrix)` affine
transform, retained by iOS as `tVector::operator*=(tMatrix)`. The full matrix is
passed by value (`thiscall`, 0x40-byte stack cleanup), and the body preserves the
source vector through a stack `Vec3` before writing x/y/z. Native establishes no
EAX result and both callers discard it.

2026-07-14 operator ownership: the real void operator definition and both
direct `vector *= matrix` callsites preserved the then-existing 85.00%, 40/40
body and both caller baselines. Android exposes the analogous operation under
`tVector::Multiply(const tMatrix&)`; Windows' by-value ABI agrees with the iOS
operator instead.

2026-07-14 exact closure: all three output lanes in native spell each product
as `matrix component * source component`. The previous x lane alone reversed
those commutative operands, causing VC6 to hoist the first matrix load ahead of
the aggregate source copy. Making x consistent with the already-exact y and z
lanes restores the native copy-before-arithmetic schedule and closes the body
to 40/40 instructions without masking or artificial dependencies. The exact
`update_snail_skin` caller remains 44/44, and partial `render_game_frame`
remains at 45.43% with all 26 operands clean.
