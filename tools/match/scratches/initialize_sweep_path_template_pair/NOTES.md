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

2026-07-03 width-local lifetime: the right-side constant is not needed until
after the three left lead-in samples. Delaying the `right` local until after
that seed loop moves focused Wibo from 13.88% (544/652) to 14.30% (537/652),
with masked operands improving from 24 ok, 0 unresolved, 1 mismatch to 26 ok,
0 unresolved, 1 mismatch.

Rejected: applying the snake-style integer Z-index helper spelling regressed
focused Wibo to 14.17% (534/652) and worsened the masked audit to 22 ok,
0 unresolved, 4 mismatch, so sweep keeps the float-Z helper argument.

Rejected: swapping the strip-mesh allocation calls to request facequads before
vertices stayed at 14.30% (537/652) and simply flipped the single masked
mismatch from target `request_object_vertices` vs candidate
`request_object_facequads` to the reverse pairing. The retained order remains
vertices before facequads.

2026-07-03 direct sample loops: expanding the three lead-in samples, three
lead-out samples, and curved body from the generic pair helper follows the
decompiler shape. The lead-in/tail loops keep the index float conversion after
primary identity, the curved body reloads the seeded primary `center_x`, and
secondary Y derives from the written primary Y. Focused Wibo moves from 14.30%
(537/652) to 14.85% (533/652), with masked operands improving from 26 ok,
0 unresolved, 1 mismatch to 27 ok, 0 unresolved, 1 mismatch.
