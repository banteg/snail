# Pinned — 71.89%, 112/105 insns

Semantics complete: extract quaternion from the 3x3 (matrix-arg ctor),
copy to a working quat, snap |x|,|y|,|z| < 0.001 to zero (w untouched),
then either rebuild directly from the snapped quat (axis collapsed) or
convert to axis-angle, scale the ANGLE by alpha, recompose
quat -> matrix. Quirk preserved: when the extracted angle is exactly
zero the matrix is left untouched (no rebuild on that path).

Residuals: copy-propagation whims (second epsilon compares read the
extracted slot instead of working), tail rebuild-copy scheduling.
Combined with linear_interpolate_matrix this fully specifies native
pose interpolation for the cluster-1 mirror transform lane.

2026-06-20 Quaternion consolidation: this scratch now consumes the shared
`include/quaternion.h` layout. Rewriting the extract step as
`extracted.initialize_quaternion_from_matrix(...)` cleared the type report but
regressed the focused matcher to 65.12% with only a 4-instruction prefix, so the
constructor spelling is retained. Focused rerun remains pinned at 71.89%,
112/105 instructions, 30-instruction prefix, with 12 masked operands OK and the
two known call-symbol mismatches.
