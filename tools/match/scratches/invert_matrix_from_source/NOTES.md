# invert_matrix_from_source @ 0x44d330

Exact match: 100.00%, 55/55 instructions.

Builds an inverse transform from a source matrix into the destination matrix:
the 3x3 basis is transposed, the position is written as negative dot products,
the basis `w` lanes are zeroed, and the position `w` lane is set to one.

The native helper is a destination-member thiscall and returns null after
writing the output matrix.
