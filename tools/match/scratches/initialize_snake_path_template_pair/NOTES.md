# initialize_snake_path_template_pair

Honest starter scratch for `initialize_snake_path_template_pair @ 0x423580`.

The callsite passes six stack arguments and the native epilogue is `ret 0x18`.
The first float-like slot is preserved even though the recovered constructor
body uses the width and texture slots. The scratch models the six straight
lead-in nodes, three lead-out nodes, the raised snake body, fixed-right
orientation, delta generation, mesh quads, and `finalize_path_template`.

Residuals are expected; this is intentionally semantic starter source rather
than an instruction-scheduled near match.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 8.90% (112/652
candidate/target instructions) to 13.74% (542/652), with masked operands
improving from 8 ok, 0 unresolved, 5 mismatch to 23 ok, 0 unresolved, 4
mismatch.

2026-07-03 Phase B pass: reloading primary and secondary sample X from the
primary `center_x` field instead of the constant argument moves focused Wibo to
13.98% (535/652), with masked operands unchanged at 23 ok, 0 unresolved, 4
mismatch.

2026-07-03 width-local lifetime: the width-derived `right` value is only used by
the right lead-out and raised body samples, not the six zero lead-in samples.
Delaying that local until after the lead-in seed loop moves focused Wibo from
13.98% (535/652) to 14.49% (535/652), with masked operands improving from
23 ok, 0 unresolved, 4 mismatch to 25 ok, 0 unresolved, 4 mismatch.

2026-07-03 Z-index helper spelling: keep the sample helper argument as an
integer index and perform the int-to-float Z conversion inside the inlined
helper after the primary identity call. Focused Wibo moves from 14.49%
(535/652) to 14.53% (532/652), with masked operands unchanged at 25 ok,
0 unresolved, 4 mismatch.

2026-07-03 orientation-bound probe rejected: extending the identity-orientation
branch from `current_index <= first_index` to `current_index <= first_index + 1`
did not change focused Wibo (14.53%, 532/652) or the masked audit (25 ok,
0 unresolved, 4 mismatch). The native `set_matrix_rotation_identity` vs
candidate `normalize_vector` pairings therefore remain treated as alignment
drift rather than a retained semantic change.

2026-07-03 middle-loop expansion: expanding the curved body sample setup out of
the generic pair helper matches the native ordering better. The center reloads
the seeded right-side sample, primary Y is computed after primary identity, and
secondary Y recomputes the cosine-derived height after secondary identity.
Focused Wibo moves from 14.53% (532/652) to 15.50% (535/652), with masked
operands improving from 25 ok, 0 unresolved, 4 mismatch to 29 ok, 0 unresolved,
3 mismatch. Retesting the `current_index <= first_index + 1` orientation-bound
probe against this expanded body stayed exactly neutral at 15.50%, so the
original bound remains retained.

Rejected: expanding the six lead-in samples and three lead-out samples from the
generic pair helper regressed focused Wibo from 15.50% (535/652) to 15.41%
(542/652), with the masked audit unchanged at 29 ok, 0 unresolved, 3 mismatch.
The lead/tail helper shape stays retained despite the decompiler's flattened
loops.

Rejected: spelling the curved body with a separate zero-based logical counter
for angle/Z, like the decompiler, regressed focused Wibo from 15.50% (535/652)
to 15.46% (538/652). The masked audit stayed at 29 ok, 0 unresolved,
3 mismatch, so the `i - 6` angle spelling remains retained for now.
