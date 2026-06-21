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
