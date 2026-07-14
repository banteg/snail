# Exact — 100.00%, 61/61 insns

The call chain and blend are unambiguous (the iteration's purpose):
out = invert(from); out *= to; interpolate_matrix_rotation(out, alpha);
out = from * out; orthogonalize_matrix(out); then translation blends
linearly through explicit `Vector3` temporaries:
`to_weighted = alpha * to.position`, `from_weighted = (1-alpha) *
from.position`, then `position = from_weighted + to_weighted`.

The explicit weighted-vector staging is the exact source shape. Scalar lane
locals left the translation blend mostly on the x87 stack and only reached
51.79%; a single staged output `Vector3` improved to 54.87% but still missed
the native 0x24-byte local frame. Three `Vector3` temporaries recover the target
frame, x87 spill/reload schedule, and final aggregate position copy with six
clean masked operands.

Consequence recorded in the invalidation ledger: native sample-pose
interpolation is rotation-space with re-orthogonalization, NOT the
per-basis-vector lerp+normalize the runner uses.

2026-07-14 multiplication-owner pass: the call chain now uses the recovered
void const-reference matrix APIs directly: invert from `from`, multiply by
`to`, premultiply by `from`, and orthogonalize. The natural member spellings
remain exact at 61/61 instructions with all six operands clean.
