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
