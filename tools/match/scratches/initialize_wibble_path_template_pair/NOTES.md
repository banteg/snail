# initialize_wibble_path_template_pair

Starter reconstruction for `initialize_wibble_path_template_pair @ 0x4289a0`.

Captures the fixed 32-sample wibble template: endpoint samples, sinusoidal
interior up-vector wobble, secondary sample offset, delta recomputation,
generated strip mesh, and finalization.

The remaining mismatch is source-shape/codegen debt, especially the decompiler's
pointer-shaped loop counters and the shared mesh tail. No dummy symbols, inline
assembly, flag changes, or volatile/register games were introduced.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 9.41% (115/608
candidate/target instructions) to 22.54% (510/608), with masked operands
improving from 7 ok, 0 unresolved, 8 mismatch to 20 ok, 0 unresolved, 4
mismatch.

2026-07-03 retained helper/copy scalar cleanup: sample setup now omits the
scratch-only `lateral_source` store and orders scalar stores/copies as
`rotation_scalar_98`, `rotation_scalar_94`, `special_scalar`, `lateral_scale`.
Focused Wibo moves from 22.54% (510/608) to 22.70% (502/608), with masked
operands unchanged at 20 ok, 0 unresolved, 4 mismatch.

2026-07-03 retained interior-X cleanup: the native interior loop stores the
interpolated lateral value in `center_x` but leaves transform `position.x` at
0.0f. Spelling that through the sample initializer moves focused Wibo from
22.70% (502/608) to 22.72% (501/608), with masked operands unchanged at 20 ok,
0 unresolved, 4 mismatch.

2026-07-03 retained roll schedule cleanup: recomputing
`sine(roll_phase) * 0.30000001f` separately for the cosine and sine basis-up
components, with `roll_phase` materialized before sample initialization but the
outer roll calls after it, moves focused Wibo from 22.72% (501/608) to 24.46%
(504/608), clearing the masked audit from 20 ok, 0 unresolved, 4 mismatch to
27 ok, 0 unresolved, 0 mismatch. Rejected/lesser splits were: folded roll
schedule after init at 23.86% with one mismatch, split turn phase before init at
23.84% with one mismatch, and roll calls after init at 23.92% with one
mismatch.

2026-07-04 retained mesh-face loop cleanup: replacing the direct two-face
`a`/`b` writes with the shared two-iteration `face_index` loop and single
`uv[3].v` tail store moves focused Wibo from 24.46% (504/608) to 29.95%
(514/608), with masked operands improving from 27 ok, 0 unresolved,
0 mismatch to 29 ok, 0 unresolved, 0 mismatch.

2026-07-13 terminal ownership: replacing the helper's `primary_last` and
`secondary_last` aliases with direct count-relative stores through the two
`Path` sample arrays moves focused Wibo from 29.95% (514/608) to 31.86%
(522/608), while the masked audit remains clean at 29 ok, 0 unresolved,
0 mismatch. Expanding the preceding delta loop into the method regressed the
score to 30.84% (527/608) and introduced one masked call mismatch, so `wibble`
retains local loop pointers and only the terminal stores carry direct owner
shape.
