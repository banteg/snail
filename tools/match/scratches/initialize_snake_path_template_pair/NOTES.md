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

2026-07-03 Phase B pass: reloading primary and secondary sample X from the
primary `center_x` field instead of the constant argument moves focused Wibo to
13.98% (535/652), with masked operands unchanged at 23 ok, 0 unresolved, 4
mismatch.

2026-07-03 width-local lifetime: the width-derived `right` value is only used by
the right lead-out and raised body samples, not the six zero lead-in samples.
Delaying that local until after the lead-in seed loop moves focused Wibo from
13.98% (535/652) to 14.49% (535/652), with masked operands improving from
23 ok, 0 unresolved, 4 mismatch to 25 ok, 0 unresolved, 4 mismatch.

2026-07-03 Z-index helper spelling: keep the sample helper argument as an
integer index and perform the int-to-float Z conversion inside the inlined
helper after the primary identity call. Focused Wibo moves from 14.49%
(535/652) to 14.53% (532/652), with masked operands unchanged at 25 ok,
0 unresolved, 4 mismatch.
