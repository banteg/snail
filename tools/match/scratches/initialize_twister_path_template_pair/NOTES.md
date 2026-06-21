# initialize_twister_path_template_pair

Starter reconstruction for `initialize_twister_path_template_pair @ 0x42a540`.

Models the 34-sample twister template with handedness-dependent phase, sinusoidal
vertical offset, previous-sample orientation reconstruction, delta recomputation,
generated mesh, facequads, and finalization.

The scratch keeps the real six-argument constructor signature used by the path
bank callsites, including the unused vertical texture argument. Remaining work is
register scheduling and exact loop form.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 10.97% (125/677
candidate/target instructions) to 14.36% (590/677), with masked operands
improving from 11 ok, 0 unresolved, 8 mismatch to 26 ok, 0 unresolved, 3
mismatch.
