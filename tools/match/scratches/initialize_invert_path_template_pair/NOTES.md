# initialize_invert_path_template_pair

Starter reconstruction for `initialize_invert_path_template_pair @ 0x429250`.

Models the fixed 34-sample invert template with `0x29` kind, runtime flag `+0x9c`
set, terminal `pi` rotation scalar, half-angle interior rotation scalar,
secondary offsets, deltas, strip mesh generation, and finalization.

Residuals should be attacked by reshaping the interior loop and mesh tail; this
starter deliberately avoids normalizer gaming.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 8.66% (116/600
candidate/target instructions) to 20.20% (509/600), with masked operands
improving from 7 ok, 0 unresolved, 7 mismatch to 14 ok, 0 unresolved, 2
mismatch.
