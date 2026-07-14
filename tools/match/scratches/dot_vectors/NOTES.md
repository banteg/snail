# Vector3::dot_vectors @ 0x44cb50

Exact static two-argument dot-product overload. Its stdcall ABI has no receiver,
but Android independently preserves the authored namespace as
`tVector::Dot(const tVector&, const tVector&)`; the adjacent one-argument
overload is already recovered as `Vector3::dot_vector`.

The exact `Vector3::normalize_vector` caller now names this static owner
directly. Both functions remain instruction-for-instruction exact.
