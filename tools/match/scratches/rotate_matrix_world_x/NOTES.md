# rotate_matrix_world_x @ 0x44ce30

Exact match: 100.00%, 50/50 instructions.

Applies an in-place local-X rotation by mixing the up and forward basis vectors
with the shared sine/cosine table helpers. The x/y lanes write the preserved
new-up temporary before the z lane writes both final temporaries.

2026-07-14 owner correction: iOS and Android both retain this exact member as
`tMatrix::RotLocalX(float)`. Mixing the receiver's own up/forward basis rows is
also direct local-axis evidence; "world" was only the old Windows analysis
label. The scratch now defines `TransformMatrix::rotate_matrix_local_x`, keeps
the stable dashboard identity through `SYMBOL`, and remains 50/50 exact.
