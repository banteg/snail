# Audit-pending exact stream — 100.00%, 105/105 insns

Semantics complete: extract quaternion from the 3x3 (matrix-arg ctor),
copy to a working quat, snap |x|,|y|,|z| < 0.001 to zero (w untouched),
then either rebuild directly from the snapped quat (axis collapsed) or
convert to axis-angle, scale the ANGLE by alpha, recompose
quat -> matrix. Quirk preserved: when the extracted angle is exactly
zero the matrix is left untouched (no rebuild on that path).

The normalized instruction stream and full 105-instruction prefix are exact.
The retained source uses the recovered `Axis`/`Quaternion`/`TransformMatrix`
member-call surfaces, which restores the native `thiscall` helper ABI. Narrow
volatile reads on the working quaternion's y/z epsilon checks prevent VC6 from
copy-propagating those reads back to the extracted quaternion slots.

One relocation audit mismatch remains: the exact call at target `0x44d5d0` is
named `initialize_quaternion_from_matrix` by the function manifest, while the
candidate object names the same matrix-argument constructor
`??0Quaternion@@QAE@PBM@Z`. This is an overloaded-symbol provenance issue, not
an instruction mismatch, so the scratch remains audit-pending rather than
proof-grade.

Combined with linear_interpolate_matrix this fully specifies native pose
interpolation for the cluster-1 mirror transform lane.

2026-06-20 Quaternion consolidation: this scratch now consumes the shared
`include/quaternion.h` layout. Rewriting the extract step as
`extracted.initialize_quaternion_from_matrix(...)` cleared the type report but
regressed the focused matcher to 65.12% with only a 4-instruction prefix, so the
constructor spelling is retained.

2026-07-09 member-ABI recovery: replacing scratch-local cdecl conversion
helpers with the recovered member calls raised the focused result from 71.89%
(112/105 instructions, 30-instruction prefix, 12 masked operands OK and two
mismatches) to 96.19% with exact instruction-count parity. Volatile y/z reads
then removed the final four normalized stack-slot differences, yielding
100.00%, 105/105 instructions, a 105-instruction prefix, 16 masked operands OK,
and the single overloaded-constructor name mismatch described above.
