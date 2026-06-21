# initialize_hill_valley_path_template_pair

Starter reconstruction for `initialize_hill_valley_path_template_pair @ 0x42d570`.

Models the family-10 hill/valley initializer: length-derived sample count,
centered/non-centered X placement, cosine vertical profile, previous-sample
orientation, secondary samples, deltas, mesh, facequads, and finalization.

Residual mismatch is expected around the loop form and x87 conversion of the
length argument. No toolchain or source fakery was used.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 7.58% (124/668
candidate/target instructions) to 12.31% (583/668), with masked operands
improving from 7 ok, 0 unresolved, 5 mismatch to 19 ok, 0 unresolved, 3
mismatch.
