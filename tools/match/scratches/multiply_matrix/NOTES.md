# multiply_matrix @ 0x44d1d0

Exact 4/4 `TransformMatrix::multiply_matrix(const TransformMatrix&)` member,
used twice by the LoopBow path-template constructor. It pushes the rhs argument
and calls the multiply-assignment operator at `0x44d1a0`, preserving the
incoming matrix receiver in ECX.

## 2026-07-24 authored member identity

Android preserves the ownership relation directly: its
`tMatrix::Multiply(const tMatrix&)` symbol branches to the adjacent
`tMatrix::operator*=(const tMatrix&)` implementation. iOS exports both symbols,
and both mobile LoopBow constructors call `Multiply`, not the operator, at the
two sites that call this Windows entry. The old anonymous-forwarder label is
therefore retired in favor of the authored member name.

The function is honestly void and takes a const reference. Its canonical source
spelling remains 4/4 exact with the operator call operand clean.
