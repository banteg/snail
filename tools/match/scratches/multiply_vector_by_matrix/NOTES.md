# multiply_vector_by_matrix @ 0x44cb90

Near-exact match: 85.00%, 40/40 instructions.

In-place affine vector transform with the matrix passed by value. The scratch
matches the native ABI (`thiscall`, 0x40-byte stack cleanup) and preserves the
source vector through a stack `Vec3` before writing x/y/z.

Residual: VC6 schedules the first matrix-column load before the native
source-vector copy and then uses the same arithmetic in a different x87 load
order. The remaining diff is scheduling only; the transform semantics and
by-value matrix ABI are pinned.

2026-06-20 larger-helper pass: rewriting the three dot products in native
`source.z`, `source.y`, `source.x` arithmetic order regressed to 62.50% because
VC6 pulled the first matrix load ahead of the source-vector copy. Keep the
current expression order; the residual is still scheduling, not a different
affine transform.
