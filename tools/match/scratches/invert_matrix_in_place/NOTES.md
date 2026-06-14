# invert_matrix_in_place @ 0x44d280

Exact match: 100.00%, 54/54 instructions.

Copies the destination transform to a stack temporary, transposes the 3x3 basis
into the destination, then rewrites the position as the negative dot product of
the original position against each original basis axis.

The expression order on `position.x` matters for VC6's x87 schedule. The final
source keeps the source-shaped matrix inverse and does not rely on alias tricks.
