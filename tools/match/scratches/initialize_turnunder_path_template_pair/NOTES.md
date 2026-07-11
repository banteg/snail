# initialize_turnunder_path_template_pair

Starter reconstruction for `initialize_turnunder_path_template_pair @ 0x427fe0`.

This scratch follows the recovered path-template family shape: local
`Path` overlay, `0x27` kind, computed `radius * 2pi + 8`
sample count, six straight lead-in samples, two straight exit samples, nonlinear
interior samples, recomputed deltas, generated strip mesh, and
`finalize_path_template`.

Residuals are expected in the induction variables, x87 temporary scheduling, and
mesh/face loop register allocation. No flags or fakematching tricks were used.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 8.37% (197/687
candidate/target instructions) to 14.79% (598/687), with masked operands
improving from 6 ok, 0 unresolved, 10 mismatch to 13 ok, 0 unresolved, 7
mismatch.

2026-07-03 path-template seed-loop sweep: delayed the `turns * 2pi`
conversion until after the header stores, split straight lead-in/exit samples
into a native-style primary/secondary initializer, set straight-sample
`delta_length`, and reload the nonlinear interpolation endpoints from the
seeded primary sample centers. Focused Wibo moved from 14.79% (598/687) to
20.96% (582/687), with masked operands improving from 13 ok, 0 unresolved, 7
mismatch to 22 ok, 0 unresolved, 5 mismatch. Rejected adjacent probes: swapping
the start/end center expressions regressed to 20.80%, and materializing
`interior_count_f` / `radius = interior_count_f * 0.15915494f` before allocation
regressed to 20.33% despite one extra clean masked operand.

2026-07-03 scalar-order cleanup probe: applying the sibling sample-scalar
spelling (`rotation_scalar_98`, `rotation_scalar_94`, `special_scalar`,
`lateral_scale`) and removing scratch-only `lateral_source` traffic regressed
focused Wibo from 20.96% (582/687) to 18.08% (563/687), with masked operands
dropping from 22 ok, 0 unresolved, 5 mismatch to 19 ok, 0 unresolved, 5
mismatch. Left out; the current turnunder layout still depends on the older
scalar traffic until the interior loop shape is rebuilt.

2026-07-03 retained mesh-face loop: replacing the direct `a`/`b` face writes
with the two-texture `face_index` loop moves focused Wibo from 20.96% (582/687)
to 23.92% (592/687). Masked operands improve from 22 ok, 0 unresolved,
5 mismatch to 24 ok, 0 unresolved, 5 mismatch. The remaining audit debt stays
in the turn angle/interior orientation schedule.

2026-07-04 retained interior-loop schedule: switched the nonlinear body to the
recovered negative one-turn angle, count-derived radius, native-style
half-angle/full-angle/Y/roll trig order, and primary `basis_forward` /
`basis_right` construction before copying the secondary lane. Focused Wibo moves
from 23.92% (592/687) to 27.22% (628/687), with masked operands improving from
24 ok, 0 unresolved, 5 mismatch to 38 ok, 0 unresolved, 1 mismatch. Retesting
the prologue-radius lifetime clears the masked audit at 37 ok, 0 unresolved,
0 mismatch, but lowers focused Wibo to 26.62%, so the retained source keeps the
loop-local radius spelling for now.
