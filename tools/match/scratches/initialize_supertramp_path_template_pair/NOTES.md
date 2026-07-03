# initialize_supertramp_path_template_pair

Honest starter scratch for `initialize_supertramp_path_template_pair @ 0x423f10`.

The native tail is `ret 0x1c`, matching seven explicit stack arguments. This
constructor allocates an extra sample before decrementing `segment_count`, then
uses the final allocated sample directly in the mesh. The scratch models the
flat approach, circular supertramp arc, separate secondary radius, direct mesh
rows, deltas, and finalization.

Residuals are expected.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 8.62% (144/552
candidate/target instructions) to 15.61% (473/552), with masked operands
improving from 4 ok, 0 unresolved, 6 mismatch to 23 ok, 0 unresolved, 4
mismatch.

2026-07-03 arc schedule cleanup: native initializes both primary and secondary
arc sample positions before orienting either sample. Moving primary orientation
after the secondary position writes and reloading secondary X from the written
primary `center_x` moves focused Wibo from 15.61% to 16.20% (473/552 unchanged),
shrinks the candidate stack frame from 0x48 to 0x44, and improves masked
operands from 23 ok, 0 unresolved, 4 mismatch to 25 ok, 0 unresolved, 2
mismatch.

2026-07-03 Z-index helper spelling: keep the flat lead-in pair helper Z input
as an integer sample index and perform the int-to-float conversion inside the
inlined helper after primary identity. Focused Wibo moves from 16.20% to
16.59% (473/552 unchanged), with masked operands unchanged at 25 ok, 0
unresolved, 2 mismatch.

2026-07-03 allocation-count spelling: materializing
`last_segment_index = curve_segments + 7`, then deriving `segment_count` from
that local, matches the target's `add 0x7` / `inc` count setup. Focused Wibo
moves from 16.59% (473/552) to 16.96% (474/552), with masked operands improving
from 25 ok, 0 unresolved, 2 mismatch to 26 ok, 0 unresolved, 1 mismatch.
Rejected adjacent probe: reloading flat lead-in helper X from the written
primary `center_x` regressed the focused score to 16.75% (475/552) and restored
the two masked mismatches, so the flat helper keeps the constant X argument.

Rejected: materializing a separate `curve_segments_f` float local for both
radius and angle division, like the decompiler's stored float count, was exactly
neutral at 16.96% (474/552) with masked operands unchanged at 26 ok,
0 unresolved, 1 mismatch. The shorter direct casts remain retained.

2026-07-03 rejected facequad inner-loop probe: unlike `sweep`/`snake` and the
twister twins, replacing the direct `a`/`b` facequad writes with a two-iteration
`face_index` loop regressed focused Wibo from 16.96% (474/552) to 10.19%
(488/552), and regressed the masked audit from 26 ok, 0 unresolved, 1 mismatch
to 7 ok, 0 unresolved, 3 mismatch. The cap-texture mesh keeps the direct
facequad writes for now.

2026-07-03 neutral flat lead-in expansion: expanding the seven flat lead-in
samples out of `initialize_pair_sample`, while keeping the earlier rejected
`center_x` reload out, was exactly neutral at 16.96% (474/552), with masked
operands unchanged at 26 ok, 0 unresolved, 1 mismatch. The helper-routed source
stays retained until a non-neutral lifetime lead appears.

2026-07-03 rejected arc-loop scalar probes: removing the arc secondary sample's
scalar-field writes regressed focused Wibo from 16.96% (474/552) to 16.49%
(467/552) and worsened the masked audit to 22 ok, 0 unresolved, 2 mismatch.
Reloading arc primary transform X from `primary->center_x`, matching the
decompiler spelling, also regressed to 16.76% (474/552) with 25 ok,
0 unresolved, 2 mismatch. The retained arc loop keeps those scalar writes and
the constant primary X store.

2026-07-03 retained mesh-vertex staging: like `start`, routing the row vertex
calculation through a local `Vector3 generated_position` before assigning
`*vertex` improves the focused matcher from 16.96% (474/552) to 17.10%
(477/552). The masked audit stays at 26 ok, 0 unresolved, 1 mismatch, and the
cap-texture facequad writes remain direct because the earlier two-iteration
`face_index` probe regressed sharply.

2026-07-04 retained mesh request-order cleanup: after mesh-vertex staging,
requesting facequads before vertices moves focused Wibo from 17.10% (477/552)
to 18.66% (477/552), and improves masked operands from 26 ok, 0 unresolved,
1 mismatch to 27 ok, 0 unresolved, 1 mismatch. The remaining mismatch still
pairs a native orientation call against the local mesh allocation call, so the
cap-texture face writer and larger frame residual stay explicit.

2026-07-03 neutral ownership retests after mesh-vertex staging: re-expanding
the seven flat lead-in samples out of `initialize_pair_sample` remained exactly
neutral at 17.10% (477/552), with masked operands unchanged at 26 ok,
0 unresolved, 1 mismatch. Rewriting the arc loop to address samples through an
explicit byte offset was also neutral at 17.10% (477/552) with the same masked
audit. Keep the helper-routed lead-in and indexed arc pointers until a
non-neutral lifetime lead appears.
