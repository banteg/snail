# initialize_axis_from_quaternion @ 0x44d580

Exact match: 100.00%, 30/30 instructions.

Converts a quaternion into axis-angle form by using exact `arccosine(w)` as the
half-angle, dividing xyz by `sine(half_angle)`, and storing `angle =
half_angle + half_angle`.
