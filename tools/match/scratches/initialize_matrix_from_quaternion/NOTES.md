# initialize_matrix_from_quaternion @ 0x44d820

Proof-grade match: 100.00%, 82/82 instructions, 3 clean masked operands.

Builds a rotation matrix from a quaternion and resets translation/homogeneous
lanes to identity values. The scratch follows the native product names and row
assignments recovered from the decompiler.

The product locals, row assignments, zero stores, and identity homogeneous lane
now match native. The key source shape is spelling doubled matrix terms as
`2.0f * (...)`, which preserves the native x87 doubling and stack-slot schedule.

2026-06-20 quaternion math pass: rewriting the nine rotation entries from
repeated add/sub chains to `2.0f * (...)` equivalents raises the scratch from
73.05% to proof-grade 100.00%. The semantic formulas are unchanged; the
accepted spelling matches native's doubled-term source idiom and avoids the old
extra stack slots and delayed zero-store schedule.
