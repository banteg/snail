# orthogonalize_matrix @ 0x44d3d0

Near-exact match: 92.31%, 24/26 instructions.

This compact matrix-basis repair helper normalizes the right/up/forward basis
vectors, then rebuilds the right and forward vectors through exact
`cross_vectors` calls.

Residual: the only mismatch is thiscall setup order for the two cross-product
calls. Native pushes both arguments before moving the destination vector into
`ecx`; the source-shaped member calls move `ecx` first, then push arguments.
