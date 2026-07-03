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

2026-07-03 path-template secondary-order sweep: delayed the length-to-steps
conversion until after the first header writes, narrowed secondary sample
initialization to transform-only writes, copied secondary X from the primary
center field, delayed loop primary `y` / `z` stores until after identity, and
added a loop-specific secondary initializer that recomputes the cosine-derived
height after secondary identity. Focused Wibo moves from 12.31% (583/668) to
14.62% (563/668), with masked operands improving from 19 ok, 0 unresolved, 3
mismatch to 27 ok, 0 unresolved, 2 mismatch.

Rejected probe: recomputing the centered/non-centered center for the last
endpoint reduced the remaining mask audit to one mismatch, but lowered the
focused fuzzy score to 13.56% and grew the candidate to 571/668, so it was not
retained.

2026-07-03 retained sample-scalar cleanup: primary sample setup now omits the
scratch-only `lateral_source` zero store and follows the native scalar store
order: `rotation_scalar_98`, `rotation_scalar_94`, `special_scalar`,
`lateral_scale`. Focused Wibo moves from 14.62% (563/668) to 14.65%
(561/668), with masked operands unchanged at 27 ok, 0 unresolved, 2 mismatch.
