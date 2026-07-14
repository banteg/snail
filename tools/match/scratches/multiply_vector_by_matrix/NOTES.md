# multiply_vector_by_matrix @ 0x44cb90

Near-exact match: 85.00%, 40/40 instructions.

This is the Windows void `Vector3::operator*=(TransformMatrix)` affine
transform, retained by iOS as `tVector::operator*=(tMatrix)`. The full matrix is
passed by value (`thiscall`, 0x40-byte stack cleanup), and the body preserves the
source vector through a stack `Vec3` before writing x/y/z. Native establishes no
EAX result and both callers discard it.

Residual: VC6 schedules the first matrix-column load before the native
source-vector copy and then uses the same arithmetic in a different x87 load
order. The remaining diff is scheduling only; the transform semantics and
by-value matrix ABI are pinned.

2026-06-20 larger-helper pass: rewriting the three dot products in native
`source.z`, `source.y`, `source.x` arithmetic order regressed to 62.50% because
VC6 pulled the first matrix load ahead of the source-vector copy. Keep the
current expression order; the residual is still scheduling, not a different
affine transform.

2026-06-21 near-match scheduler audit: focused Wibo still reports 85.00%,
40/40 instructions, no masked operands. Adding scalar `source_x/source_y/source_z`
locals after the source-vector copy is codegen-neutral and does not prevent VC6
from hoisting the first matrix load before the native source-copy stores.
Combining those locals with the native z/y/x dot-product term order regresses to
77.50% by disturbing the final z-lane x87 schedule. Keep the compact aggregate
`Vector3 source = *this` plus current expression order; the mismatch remains a
source-scheduler artifact, not evidence for a different matrix ABI.

2026-06-20 presentation-helper audit: focused Wibo remains 85.00%, 40/40
instructions, with no masked operands. Rechecking this next to
`update_sprite_facing_angle` confirms the residual class is the same kind of
caller/local scheduler debt: native copies the source vector before the first
matrix-column `fld`, while VC6 hoists that `fld` ahead of the copy under all
source-plausible shapes tried so far. Keep the by-value matrix ABI and aggregate
source copy pinned.

2026-07-14 operator ownership: the real void operator definition and both
direct `vector *= matrix` callsites preserve the existing 85.00%, 40/40 body and
both caller baselines. Android exposes the analogous operation under
`tVector::Multiply(const tMatrix&)`; Windows' by-value ABI agrees with the iOS
operator instead. The remaining body differences are still honest x87
scheduling debt.
