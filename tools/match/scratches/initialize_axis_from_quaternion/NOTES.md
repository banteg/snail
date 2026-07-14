# initialize_axis_from_quaternion @ 0x44d580

Exact match: 100.00%, 30/30 instructions.

Converts a quaternion into axis-angle form by using exact `arccosine(w)` as the
half-angle, dividing xyz by `sine(half_angle)`, and storing `angle =
half_angle + half_angle`.

2026-06-20 type consolidation: the axis-angle owner now lives in
`include/axis.h` with the four-float layout and the
`initialize_axis_from_quaternion` method.
Focused rerun remains exact at 100.00%, 30/30 instructions, with 4 masked
operands OK. `initialize_quaternion_from_axis` uses the same header and keeps
its existing x87 scheduling residual unchanged.

2026-07-14 owner-name closure: `AxisAngle` is the canonical Windows owner name,
proven by the folded default-constructor call used by interpolation. `Axis`
remains a compatibility alias for Android's `tAxis`; no second layout exists.
