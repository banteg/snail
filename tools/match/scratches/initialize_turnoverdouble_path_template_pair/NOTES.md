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

2026-07-03 retained mesh-face loop: replacing the direct `a`/`b` face writes
with the two-iteration `face_index` loop moves focused Wibo from 23.98% (571/680)
to 27.60% (581/680). Masked operands improve from 32 ok, 0 unresolved,
1 mismatch to 34 ok, 0 unresolved, 1 mismatch; the remaining mismatch is still
the sine/cosine pairing in the curved interior.

2026-07-04 cosine-center probe rejected: replacing the center-X expression
`sine(slalom_angle + 1.5707964f) * left` with the semantic equivalent
`cosine(slalom_angle) * left` regressed focused Wibo from 27.60% (581/680) to
25.76% (578/680). Masked operands worsened from 34 ok, 0 unresolved,
1 mismatch to 31 ok, 0 unresolved, 2 mismatch, adding a target `sine` vs
candidate `cosine` pairing before the existing target `cosine` vs candidate
`sine` residual. Keep the phase-shifted sine spelling until the surrounding
curved-call schedule changes.

2026-07-13 terminal ownership: as in `turnover`, the delta loop retains its
local sample pointers, while the two terminal writes belong directly to the
`Path` sample arrays. Replacing `last_primary` and `last_secondary` pointer
aliases with direct count-relative array stores moves focused Wibo from 27.60%
(581/680) to 28.53% (589/680). The masked audit remains 34 ok, 0 unresolved,
1 mismatch; the sole residual is still the curved sine/cosine call pairing.
