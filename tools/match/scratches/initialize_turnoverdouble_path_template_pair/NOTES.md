# initialize_turnoverdouble_path_template_pair

Honest starter scratch for `initialize_turnoverdouble_path_template_pair @ 0x427640`.

This target uses the same six-argument stack shape as turnover (`ret 0x18`),
but the interior curve performs a double roll and returns to the same lateral
side. The scratch models the recovered double-turnover angle folding, secondary
up-vector offset, deltas, strip mesh, and finalization.

Residuals are expected; the source is semantic starter code.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 9.81% (176/680
candidate/target instructions) to 23.98% (571/680), with masked operands
improving from 14 ok, 0 unresolved, 7 mismatch to 32 ok, 0 unresolved, 1
mismatch.

2026-07-03 rejected seed-X reload: applying turnover's secondary-X reload from
the primary center field reduces focused Wibo to 23.68% (570/680), so this
sibling keeps the original argument-based seed helper spelling.
