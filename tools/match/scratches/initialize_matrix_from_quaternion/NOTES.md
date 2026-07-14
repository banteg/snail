# initialize_matrix_from_quaternion @ 0x44d820

Proof-grade match: 100.00%, 82/82 instructions, 3 clean masked operands.

This is the authored `TransformMatrix(const Quaternion&)` constructor retained
by Android as `tMatrix::tMatrix(const tQuaternian&)`. The real constructor
definition remains exact without an explicit source return. It builds the
rotation basis from the quaternion and resets translation/homogeneous lanes to
identity values.

The product locals, row assignments, zero stores, and identity homogeneous lane
now match native. The key source shape is spelling doubled matrix terms as
`2.0f * (...)`, which preserves the native x87 doubling and stack-slot schedule.

2026-06-20 quaternion math pass: rewriting the nine rotation entries from
repeated add/sub chains to `2.0f * (...)` equivalents raises the scratch from
73.05% to proof-grade 100.00%. The semantic formulas are unchanged; the
accepted spelling matches native's doubled-term source idiom and avoids the old
extra stack slots and delayed zero-store schedule.

2026-07-14 constructor ownership: replacing the synthetic pointer-taking
initializer with the real const-reference constructor preserves all 82 target
instructions and all three audited operands. `interpolate_matrix_rotation` now
consumes this constructor directly as well.
