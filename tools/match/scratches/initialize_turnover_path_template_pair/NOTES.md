# initialize_turnover_path_template_pair

Honest starter scratch for `initialize_turnover_path_template_pair @ 0x426cb0`.

The constructor callsite and target tail show six stack arguments (`ret 0x18`).
The scratch models the left lead-in, right lead-out, single turnover roll,
secondary sample offset along the rotating up vector, deltas, strip mesh, and
`finalize_path_template`.

Residuals are expected; helper calls keep this readable and semantic rather
than byte-shaped.
