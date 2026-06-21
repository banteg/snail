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
