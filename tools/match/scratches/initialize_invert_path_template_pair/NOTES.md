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

2026-07-03 retained helper/copy scalar cleanup: sample setup now omits the
scratch-only `lateral_source` store and orders scalar stores/copies as
`rotation_scalar_98`, `rotation_scalar_94`, `special_scalar`, `lateral_scale`.
Focused Wibo moves from 20.20% (509/600) to 22.89% (501/600), with masked
operands improving from 14 ok, 0 unresolved, 2 mismatch to 18 ok, 0 unresolved,
2 mismatch.

2026-07-03 retained interior-X cleanup: the native interior loop stores the
interpolated lateral value in `center_x` but leaves transform `position.x` at
0.0f. Spelling that through the sample initializer moves focused Wibo from
22.89% (501/600) to 23.82% (500/600), and clears the masked audit from
18 ok, 0 unresolved, 2 mismatch to 21 ok, 0 unresolved, 0 mismatch.

2026-07-04 retained mesh-face loop cleanup: replacing the direct two-face
`a`/`b` writes with the shared two-iteration `face_index` loop and single
`uv[3].v` tail store moves focused Wibo from 23.82% (500/600) to 29.37%
(510/600), with masked operands improving from 21 ok, 0 unresolved,
0 mismatch to 23 ok, 0 unresolved, 0 mismatch.
