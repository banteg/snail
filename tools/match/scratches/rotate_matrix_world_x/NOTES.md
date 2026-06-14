# rotate_matrix_world_x @ 0x44ce30

Exact match: 100.00%, 50/50 instructions.

Applies an in-place world-X rotation by mixing the up and forward basis vectors
with the shared sine/cosine table helpers. The x/y lanes write the preserved
new-up temporary before the z lane writes both final temporaries.
