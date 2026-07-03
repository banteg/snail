# initialize_toad_path_template_pair

Starter reconstruction for `initialize_toad_path_template_pair @ 0x42cbf0`.

Captures the branch-dependent lead/exit counts, fixed width `4`, 26-sample turn
arc, Z-rotation by the recovered turn angle, secondary offsets, delta
recomputation, strip mesh generation, and finalization.

The scratch is an honest partial. The remaining gaps are the exact local/stack
shape and mesh-tail scheduling.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 9.55% (175/663
candidate/target instructions) to 19.25% (594/663), with masked operands
improving from 5 ok, 0 unresolved, 8 mismatch to 16 ok, 0 unresolved, 3
mismatch.

2026-07-03 angle-order split: spelling the turn angle as a separate `0.5f`
multiply before applying the branch sign and quarter-turn scale moves focused
Wibo to 19.40% (595/663), with masked operands improving to 18 ok, 0
unresolved, 2 mismatch. A neutral-sample/writeback probe raised the operand
count but reduced fuzzy score to 19.26%, so it was left out.

2026-07-03 parameter-width pass: focused head diff showed the native
constructor reads the branch selector as a byte (`mov al, [esp+4]`), while the
scratch declared it as an `int`. Narrowing the shared declaration and scratch
signature to `char turn_left` moves focused Wibo to 19.71% (595/663), exposes a
1-instruction prefix, and leaves masked operands unchanged at 18 ok, 0
unresolved, 2 mismatch. The remaining focused residual is stack-frame and
interior orientation/copy scheduling, not call ABI width.

2026-07-03 sample-scalar retry after ABI cleanup: after narrowing the branch
selector to `char`, removing the scratch-only `lateral_source` writes from the
primary initializer and secondary copy now improves focused Wibo from 19.71%
(595/663) to 19.79% (590/663). The 1-instruction prefix and masked audit stay
at 18 ok, 0 unresolved, 2 mismatch, so this is a small source-shape win while
the interior orientation/copy scheduling residual remains.
