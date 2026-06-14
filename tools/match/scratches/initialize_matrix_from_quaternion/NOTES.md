# initialize_matrix_from_quaternion @ 0x44d820

Source-shaped match: 73.05%, 82/82 instructions.

Builds a rotation matrix from a quaternion and resets translation/homogeneous
lanes to identity values. The scratch follows the native product names and row
assignments recovered from the decompiler.

Residual: remaining mismatch is local stack-slot assignment for the quaternion
products, equivalent doubled add/sub spelling for several matrix entries, and
scheduling of the three zero stores. No fake aliases or forced scheduling were
used to hide that debt.
