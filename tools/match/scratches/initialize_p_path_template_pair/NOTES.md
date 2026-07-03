# initialize_p_path_template_pair

Honest starter scratch for `initialize_p_path_template_pair @ 0x425a40`.

The constructor callsite shows nine explicit stack arguments and the target tail
is `ret 0x24`. The first argument selects runtime kinds `0x21..0x23`; the body
uses the width, endpoint X positions, segment count, and two track textures.

The scratch builds the endpoint samples, fills the three P-family curve formulas
seen in the decompile, derives orientation and deltas, generates the strip mesh,
and finalizes the template. Residuals are expected.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 10.58% (134/679
candidate/target instructions) to 18.55% (561/679), with masked operands
improving from 6 ok, 0 unresolved, 8 mismatch to 19 ok, 0 unresolved, 6
mismatch.

2026-07-03 path-template count/radius sweep: materialized the endpoint
`last_index = curve_segments + 1` and allocation `sample_count = last_index + 1`
spelling used by the native constructor, then kept the radius sign check on an
x87 temporary before storing the float radius. Focused Wibo moved from 18.55%
(561/679) to 19.22% (559/679), with masked operands unchanged at 19 ok, 0
unresolved, 6 mismatch. Rejected adjacent probes: reloading primary/secondary X
from `primary->center_x`, reloading secondary Y from the primary transform, and
branching on `kind - 0x21`; all reduced the focused score.

2026-07-03 Z-index helper spelling: keep the pair helper Z input as an integer
sample index and perform the int-to-float conversion inside the inlined helper
after primary identity. Focused Wibo moves from 19.22% (559/679) to 19.26%
(557/679), with masked operands unchanged at 19 ok, 0 unresolved, 6 mismatch.

2026-07-03 radius compare probe rejected: collapsing the radius sign check from
the double temporary to a float local made the visible compare use a dword
operand, but focused Wibo regressed from 19.26% (557/679) to 19.19% (561/679).
Masked operands stayed at 19 ok, 0 unresolved, 6 mismatch, so the native-shaped
temporary remains the retained spelling.
