# initialize_start_path_template_pair

Honest starter scratch for `initialize_start_path_template_pair @ 0x426400`.

The callsite passes six stack arguments and the native tail is `ret 0x18`.
Unlike the simpler terminal-row templates, this constructor allocates one extra
sample, decrements `segment_count`, and uses the final allocated sample directly
for the mesh row. The scratch models that allocation shape, the raised starting
plateau, the cosine descent, the flat tail, deltas, mesh, and finalization.

Residuals are expected.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 10.90% (124/610
candidate/target instructions) to 14.56% (530/610), with masked operands
improving from 8 ok, 0 unresolved, 6 mismatch to 23 ok, 0 unresolved, 2
mismatch.

2026-07-03 Phase B pass: spelling the allocation count through
`curve_segments + 15`, then setting `segment_count` from that local plus one,
matches the target's `add 0xf` / `inc` setup shape and shrinks the candidate
frame to `0x48`. Reloading primary and secondary X from the primary
`center_x` field instead of the constant argument then brings the final frame
to the native `0x44` and moves the focused matcher to 15.86% (525/610), with a
7-instruction prefix and masked operands at 19 ok, 0 unresolved, 2 mismatch.
An explicit count-of-11 tail loop was rejected: it made the tail counter look
more native but dropped the score to 15.63% and worsened the masked audit to
20 ok, 0 unresolved, 2 mismatch.

2026-07-03 Z-index helper spelling: keep the pair helper Z input as an integer
sample index and perform the int-to-float conversion inside the inlined helper
after primary identity. Focused Wibo moves from 15.86% (525/610) to 16.96%
(522/610), with masked operands improving from 19 ok, 0 unresolved, 2 mismatch
to 21 ok, 0 unresolved, 2 mismatch.

2026-07-03 lead-in Y lifetime rejection: spelling `radius + radius` as an
explicit `raised_y` local regresses focused Wibo from 16.96% (522/610) to
16.95% (523/610). The emitted code stores and reloads the doubled radius before
adding the secondary offset, while the current source keeps the x87 value live.
The source shape was reverted.

2026-07-03 direct sample-loop expansion: expanding the lead-in, flat tail, and
curved body samples to match the native direct setup removes the remaining
generic pair helper from the scratch. The retained shape stores primary X from
`center_x`, keeps the curved Z conversion before the cosine-derived Y, copies
the flat tail secondary Z from the written primary transform, and derives the
curved secondary Y from the written primary Y. Focused Wibo moves from 16.96%
(522/610) to 17.31% (511/610), with the 7-instruction prefix preserved and
masked operands improving from 21 ok, 0 unresolved, 2 mismatch to 22 ok,
0 unresolved, 2 mismatch. The remaining masked mismatches are still the
orientation calls aligned against the later strip-mesh allocation calls.

2026-07-03 raised-Y retry after direct loops: retesting the native-looking
`raised_y = radius + radius` local after direct sample-loop expansion still
regressed focused Wibo from 17.31% (511/610) to 17.02% (518/610). The
7-instruction prefix and masked audit stayed unchanged at 22 ok, 0 unresolved,
2 mismatch, so the inline `radius + radius` expression remains retained.

2026-07-03 retained mesh-face loop: replacing the direct `a`/`b` face writes
with a two-iteration `face_index` loop moves focused Wibo from 17.31% (511/610)
to 18.04% (521/610), with masked operands improving from 22 ok, 0 unresolved,
2 mismatch to 24 ok, 0 unresolved, 2 mismatch. This is an intentionally
qualified source-shape win: the previous 7-instruction prefix is lost and the
candidate frame grows from the native 0x44 to 0x48, so the prologue/register
lifetime debt remains open.

2026-07-03 tail-bound local rejection: replacing the flat tail upper bound
`curve_segments + 15` with the existing `last_segment_index` local regressed
focused Wibo from 18.04% (521/610) to 17.88% (520/610). The masked audit stayed
unchanged at 24 ok, 0 unresolved, 2 mismatch, so the direct expression remains
retained.

2026-07-03 neutral face-index lifetime probe: hoisting the mesh `face_index`
loop variable out of the `for` header, matching the spelling used by several
other path-template helpers, was exactly neutral at 18.04% (521/610). The
candidate frame stayed at 0x48 and the masked audit stayed at 24 ok, 0
unresolved, 2 mismatch, so the block-scoped loop variable remains.

2026-07-03 lead-in direct-index rejection: removing the primary/secondary
sample pointer locals from the first five-sample loop and spelling the writes
directly as `primary_samples[i]` / `secondary_samples[i]` regressed focused
Wibo from 18.04% (521/610) to 17.79% (537/610). The masked audit stayed at
24 ok, 0 unresolved, 2 mismatch, so the pointer locals remain retained.

2026-07-03 retained mesh-vertex staging: routing the row vertex calculation
through a local `Vector3 generated_position` before assigning `*vertex` matches
the native stack-spill shape better than direct component stores. Focused Wibo
moves from 18.04% (521/610) to 20.56% (528/610), and masked operands improve
from 24 ok, 0 unresolved, 2 mismatch to 26 ok, 0 unresolved, 2 mismatch. The
known prologue debt remains: candidate frame 0x48 versus native 0x44.

2026-07-04 retained mesh request-order cleanup: after mesh-vertex staging,
requesting facequads before vertices moves focused Wibo from 20.56% (528/610)
to 21.27% (528/610), and improves masked operands from 26 ok, 0 unresolved,
2 mismatch to 27 ok, 0 unresolved, 1 mismatch. The remaining mismatch still
pairs a native orientation call against the local mesh allocation call, so this
only narrows the allocation-call alignment debt.

2026-07-03 rejected curved byte-offset probe: replacing the curved body loop's
`primary_samples[sample_index]` / `secondary_samples[sample_index]` pointers
with an explicit `sample_offset` regressed focused Wibo from 20.56% to 18.72%
(528/610 to 533/610) and reduced the masked audit from 26 ok, 0 unresolved,
2 mismatch to 22 ok, 0 unresolved, 2 mismatch. Keep the indexed sample pointers
for the current `start` loop shape.

2026-07-04 retained tail-count retest: after mesh-vertex staging and the
facequads-first mesh request order, retesting the explicit count-of-11 flat-tail
loop now moves focused Wibo from 21.27% (528/610) to 21.65% (526/610). Masked
operands stay at 27 ok, 0 unresolved, 1 mismatch, and the prefix/frame debt
remains unchanged at candidate frame 0x48 versus native 0x44, so this is a
small current-shape win rather than a prologue fix.

2026-07-04 retained orientation scheduling expansion: spelling the curved-body
orientation work inline, with the first curved sample setting both previous
transforms to identity and later samples building primary and secondary
right-vector frames directly, moves focused Wibo from 21.65% (526/610) to
22.01% (526/610). Masked operands stay at 27 ok, 0 unresolved, 1 mismatch; the
remaining mismatch is still native orientation work aligned against the local
mesh allocation call.
