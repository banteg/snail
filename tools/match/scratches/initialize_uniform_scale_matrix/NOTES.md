# initialize_uniform_scale_matrix @ 0x44cde0

Exact match: 100.00%, 21/21 instructions.

Initializes a full 4x4 transform matrix to a uniform scale on the x/y/z diagonal,
zeroes off-diagonal and translation lanes, and writes `position.w = 1.0f`.
