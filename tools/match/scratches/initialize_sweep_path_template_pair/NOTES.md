# initialize_sweep_path_template_pair

Honest starter scratch for `initialize_sweep_path_template_pair @ 0x422c00`.

The constructor callsite passes six stack arguments and the native tail is
`ret 0x18`. The first float-like slot is preserved but not used by the
recovered body. The scratch builds the 30-node sweep with three lead-in nodes,
three lead-out nodes, cosine-shaped lateral motion, a shallow sine Y sweep,
sample deltas, strip mesh quads, and `finalize_path_template`.

Residuals are expected. This is a semantic starter with local helper routines,
not an instruction-scheduled match attempt.
