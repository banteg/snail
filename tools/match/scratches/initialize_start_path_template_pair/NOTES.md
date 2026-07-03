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
