# initialize_sweep_path_template_pair

Honest starter scratch for `initialize_sweep_path_template_pair @ 0x422c00`.

The constructor callsite passes six stack arguments and the native tail is
`ret 0x18`. The first float-like slot is preserved but not used by the
recovered body. The scratch builds the 30-node sweep with three lead-in nodes,
three lead-out nodes, cosine-shaped lateral motion, a shallow sine Y sweep,
sample deltas, strip mesh quads, and `finalize_path_template`.

Residuals are expected. This is a semantic starter with local helper routines,
not an instruction-scheduled match attempt.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 7.04% (115/652
candidate/target instructions) to 13.71% (544/652), with masked operands
improving from 4 ok, 0 unresolved, 6 mismatch to 24 ok, 0 unresolved, 1
mismatch.

2026-07-03 Phase B pass: reloading primary and secondary sample X from the
primary `center_x` field instead of the constant argument moves focused Wibo to
13.88% (544/652), with masked operands unchanged at 24 ok, 0 unresolved, 1
mismatch. A loop split with delayed sine-derived Y/Z stores was rejected: it
nudged the score only to 13.74% (556/652) while worsening the masked audit to
21 ok, 0 unresolved, 2 mismatch.
