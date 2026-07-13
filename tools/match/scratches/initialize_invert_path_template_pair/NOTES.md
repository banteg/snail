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

2026-07-13 terminal ownership: replacing `primary_last` and `secondary_last`
pointer aliases with direct count-relative stores through the two `Path` sample
arrays moves focused Wibo from 29.37% (510/600) to 31.31% (518/600). The
masked audit remains clean at 23 ok, 0 unresolved, 0 mismatch. The delta loop
retains its local sample pointers, matching the independently measured `wibble`
boundary.

2026-07-13 interior lane ownership: the native interior loop copies only the
0x40-byte `TransformMatrix`; `center_x`, rotation, special, and lateral-scale
fields remain primary-owned. Giving that loop an interior-specific transform
copy moves focused Wibo from 31.31% (518/600) to 33.94% (508/600), while the
masked audit remains clean at 23 ok, 0 unresolved, 0 mismatch. Letting the
transform-only helper also cover endpoints scored 36.03% (488/600) but
introduced two call mismatches and lost the endpoint ownership boundary.
Spelling the independently initialized endpoint transforms directly, including
the primary-only terminal pi rotation, scored 30.77% (479/600) with two call
mismatches. Those endpoint experiments were rejected; only the proved interior
ownership change is retained.

2026-07-13 interior orientation ownership: each primary sample owns the
position delta from its predecessor as `basis_forward`, normalizes that vector,
then owns `basis_right = basis_up cross basis_forward` before its 0x40-byte
transform is copied to the secondary lane. Recovering that sequence moves
focused Wibo from 33.94% (508/600) to 36.59% (537/600), with the masked audit
still clean at 25 ok, 0 unresolved, 0 mismatch.
