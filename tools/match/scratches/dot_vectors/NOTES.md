# Vector3::dot_vectors @ 0x44cb50

Exact static two-argument dot-product overload. Its stdcall ABI has no receiver,
but Android independently preserves the authored namespace as
`tVector::Dot(const tVector&, const tVector&)`; the adjacent one-argument
overload is already recovered as `Vector3::dot_vector`.

The exact `Vector3::normalize_vector` caller now names this static owner
directly. Both functions remain instruction-for-instruction exact.

2026-07-14 const-reference pass: the shared declaration and exact definition
now use the authored two-reference surface rather than pointer-shaped ABI
stand-ins. Windows still compiles to the same 11/11 instructions and `ret 8`;
Android's independently retained static overload makes the ownership explicit.
