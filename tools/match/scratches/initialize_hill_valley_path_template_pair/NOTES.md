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

2026-07-03 prologue/X reload cleanup: keep the length-to-steps conversion
before `width_or_scale`, materialize `last = steps + 1` before allocation, and
reload primary transform X from `center_x` inside the sample helper. Focused
Wibo moves from 14.65% (561/668) to 14.67% (559/668), with masked operands
unchanged at 27 ok, 0 unresolved, 2 mismatch. Rejected adjacent probe: spelling
sample 0's centered/non-centered branch directly against `primary_samples[0]`
regressed focused Wibo to 14.63% (562/668), so the existing `center_x` local is
retained.

2026-07-03 loop counter plus endpoint recompute: spelling the hill loop with
the native zero-based phase counter and pre-incremented Z counter moves the
focused score to 15.66% (558/668) on its own. Retrying the last-endpoint center
recompute in that loop shape is now retained: focused Wibo moves from 14.67%
(559/668) to 18.00% (565/668). This is not a clean call-audit win; masked
operands move from 27 ok, 0 unresolved, 2 mismatch to 26 ok, 0 unresolved,
4 mismatch, adding two orientation identity-vs-normalize pairings alongside
the existing half-scale/phase and strip-mesh allocation residuals.

2026-07-03 retained mesh-face loop: replacing the two straight face writes with
the native two-iteration `face_index` loop moves focused Wibo from 18.00%
(565/668) to 21.53% (577/668). Masked operands improve from 26 ok, 0
unresolved, 4 mismatch to 28 ok, 0 unresolved, 4 mismatch; the remaining
residuals are still the half-scale/phase pairing, two orientation call pairings,
and the vertices-vs-facequads allocation alignment.

2026-07-03 rejected loop-body probes: fully expanding the interior hill loop in
the decompiler order clears the half-scale/phase and orientation call residuals
but regresses focused Wibo from 21.53% (577/668) to 19.22% (560/668), leaving
only the mesh allocation call mismatch. A narrower center-source probe that
keeps the helper shape but initializes loop samples from
`primary_samples[0].center_x` also regresses to 19.94% (576/668), with masked
operands at 28 ok, 0 unresolved, 2 mismatch. Both probes are left out; the
current helper-routed loop keeps the better fuzzy alignment.
