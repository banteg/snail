# orthogonalize_matrix @ 0x44d3d0

Exact match: 100.00%, 26/26 instructions, five masked operands clean.

This compact matrix-basis repair helper normalizes the right/up/forward basis
vectors, then rebuilds the right and forward vectors through exact
`cross_vectors` calls.

## Source-shape win (2026-06-16): thiscall member spelling

The prior `__fastcall` free-function spelling
(`void __fastcall orthogonalize_matrix(TransformMatrix* transform)`) produced
the correct ABI (ecx = transform) and matched every instruction except the
two `cross_vectors` thiscall setups: it scheduled `mov ecx, this` before the
two argument pushes, while native pushes both arguments before moving the
destination vector into `ecx`.

Spelling the function as the `TransformMatrix` member it is in the shared
header (`void TransformMatrix::orthogonalize_matrix()`, using `this` instead
of a `transform` parameter) flips VC6's thiscall setup to the native
push-then-`mov ecx` order for both cross calls and closes the residual. The
ABI is unchanged (ecx = this on entry, `mov esi, ecx` prologue identical), so
this is the original source shape, not a flag or normalizer trick. A standalone
idiom probe confirmed the member spelling emits `push; push; mov ecx; fstp;
call` for the first cross call and `push; push; mov ecx; call` for the second,
matching native byte-for-byte; the free `__fastcall` spelling emits
`mov ecx` first in both cases.

The child layout and `cross_vectors`/`normalize_vector` ABIs are unchanged:
`this` = output for `cross_vectors`, and `normalize_vector` is the shared
`__fastcall` callsite view returning `float` (discarded with `fstp st(0)`).
