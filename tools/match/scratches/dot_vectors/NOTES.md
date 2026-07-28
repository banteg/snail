# tVector::Dot(const tVector&, const tVector&) @ 0x44cb50

Exact static two-argument dot-product overload. Its stdcall ABI has no receiver,
but Android independently preserves the authored namespace as
`tVector::Dot(const tVector&, const tVector&)`; the adjacent one-argument
overload is recovered as `tVector::Dot(const tVector&)`.

The exact `tVector::Normalize` caller now names this static owner
directly. Both functions remain instruction-for-instruction exact.

2026-07-14 const-reference pass: the shared declaration and exact definition
now use the authored two-reference surface rather than pointer-shaped ABI
stand-ins. Windows still compiles to the same 11/11 instructions and `ret 8`;
Android's independently retained static overload makes the ownership explicit.
