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

Rejected: swapping the strip-mesh allocation calls to request facequads before
vertices stayed neutral at 15.50% (535/652), with masked operands unchanged at
29 ok, 0 unresolved, 3 mismatch. It only flipped the mesh call mismatch from
target vertices vs candidate facequads to target facequads vs candidate
vertices, matching the earlier `sweep` rejection pattern.

2026-07-03 facequad inner loop: applying the same retained mesh spelling as
`sweep` emits the native two-iteration `face_index` loop and shared
`face->uv[3].v` tail store. Focused Wibo moves from 15.50% (535/652) to
21.33% (548/652), and masked operands improve from 29 ok, 0 unresolved,
3 mismatch to 33 ok, 0 unresolved, 3 mismatch. The two orientation
identity-vs-normalize pairings and the mesh request alignment pairing remain
honest residuals.

2026-07-03 half-angle cleanup: spelling the curved-body center expression as
`cosine(angle * 0.5f)` instead of materializing a `half_angle` local is focused
score neutral at 21.33% (548/652), with masked operands unchanged at 33 ok,
0 unresolved, 3 mismatch. The cleanup is retained as decompiler-shaped source
only; the same orientation and mesh-request residuals remain.

2026-07-04 retained orientation scheduling expansion: expanding the curved-body
orientation helper calls in place keeps the first curved sample's identity
branch paired across both lanes, then builds both right-vector orientation
frames inline. Focused Wibo moves from 21.33% (548/652) to 22.15% (549/652),
and masked operands improve from 33 ok, 0 unresolved, 3 mismatch to 35 ok,
0 unresolved, 1 mismatch. The remaining mismatch is only the mesh allocation
call pairing.

2026-07-04 mesh-vertex staging probe rejected: applying the `start` and
`supertramp` local `Vector3 generated_position` vertex-row staging to `snake`
regressed focused Wibo from 21.33% (548/652) to 20.55% (555/652). Masked
operands dropped from 33 ok, 0 unresolved, 3 mismatch to 31 ok, 0 unresolved,
3 mismatch, so `snake` keeps direct vertex component stores.

2026-07-04 post-orientation mesh request-order retest rejected: after the
retained orientation scheduling expansion, swapping strip-mesh allocation to
facequads-before-vertices stayed neutral at 22.15% (549/652) with masked
operands unchanged at 35 ok, 0 unresolved, 1 mismatch. The single mismatch
only flipped from target vertices vs candidate facequads to target facequads vs
candidate vertices, so the helper keeps vertices-first order.

2026-07-13 delta ownership: independently of `sweep`, the native `snake` body
also owns the primary and secondary delta loop directly. Removing the
scratch-local `compute_terminal_deltas(Path*)` alias, indexing both arrays from
the method owner, and addressing terminal samples directly as
`samples[segment_count - 1]` moves focused Wibo from 22.15% (549/652) to
30.15% (562/652). The masked audit improves from 35 ok, 0 unresolved,
1 mismatch to 37 ok, 0 unresolved, 0 mismatch. This is shared `Path` source
shape confirmed by a second target, not a copied register-lifetime trick.

2026-07-15 mesh ownership: the native vertex builder has distinct terminal-row
and ordinary-row scalar branches. Splitting the collapsed sample selection and
terminal Z ternary moves focused Wibo from 30.15% (562/652) to 30.33%
(568/652). Replacing the guarded face-column `for` with the native mutating
`do/while` then reaches 30.54% (566/652). Both changes preserve the clean
37 ok, 0 unresolved, 0 mismatch audit.

2026-07-15 induction ownership: the three departure samples recompute
`4.0 - width * 0.5` in their loop, and the native loop owns separate sample and
logical curve induction. Recomputing the departure center reaches 30.59%, and
the mutating departure `do/while` reaches 30.68%. Recovering the separate
zero-based curve counter finishes at 30.61% (570/652), a small fuzzy tradeoff
for source shape directly supported by both decompilers. Expanding the lead-in
and departure setup out of the obsolete scratch-local pair helper is codegen
neutral at that final score and makes the constructor's ownership explicit.
The masked audit remains 37 ok, 0 unresolved, 0 mismatch.

Rejected: changing the six-sample lead-in from its constant-bound `for` to an
explicit mutating `do/while` regressed focused Wibo from 30.61% (570/652) to
30.51% (574/652) without changing the clean audit. The compiler already emits
the required post-tested machine loop, so the smaller source form remains.

Not modeled: the target contains parity tests in each face branch, but both
outcomes push the same texture argument (`texture_a` for the first face and
`texture_b` for the second). Synthesizing a source-level no-op conditional
would be fakematching rather than recovered semantics, so the scratch leaves
that scheduling artifact as an honest residual.
