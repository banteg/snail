# `multiply_matrices` recovery notes

Target: `multiply_matrices @ 0x44d060` (`thiscall`, `ret 0x8`).

Core affine row-vector matrix multiply. The destination is `this`, `lhs` is the
left operand, and `rhs` is the right operand. The helper writes only the 3x3
basis rows and translated `position.xyz`; the homogeneous `w` lanes are not
touched.

2026-07-14 contract closure: Android retains the owner as
`tMatrix::Multiply(const tMatrix&, const tMatrix&)`. The exact Windows source
now takes the same two const references and returns void. Its epilogue still
leaves `rhs` in EAX because that register holds the right operand throughout
the final stores; both wrappers discard it, and removing the synthetic return
preserves all 114 instructions exactly.

2026-07-18 tracked decompile replay: Binary Ninja and IDA now both materialize
the complete `TransformMatrix` owner across all basis and position lanes. The
artifacts also preserve the recovered void ABI instead of inventing a return
from the incidental final EAX value. The exact matcher result is unchanged.
