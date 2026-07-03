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
