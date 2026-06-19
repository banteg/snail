# `multiply_matrices` recovery notes

Target: `multiply_matrices @ 0x44d060` (`thiscall`, `ret 0x8`).

Core affine row-vector matrix multiply. The destination is `this`, `lhs` is the
left operand, and `rhs` is the right operand. The helper writes only the 3x3
basis rows and translated `position.xyz`; the homogeneous `w` lanes are not
touched.

The native epilogue leaves `rhs` in `eax`, so the scratch returns `rhs` to keep
the existing in-place wrapper calls exact. That register result is not a
meaningful matrix API result.
