# initialize_turnunder_path_template_pair

Starter reconstruction for `initialize_turnunder_path_template_pair @ 0x427fe0`.

This scratch follows the recovered path-template family shape: local
`AttachmentPathTemplate` overlay, `0x27` kind, computed `radius * 2pi + 8`
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
