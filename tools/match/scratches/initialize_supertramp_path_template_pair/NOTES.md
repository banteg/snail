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
