# initialize_slalomdouble_path_template_pair

Honest starter scratch for `initialize_slalomdouble_path_template_pair @ 0x425050`.

The constructor callsite uses the same six-argument stack shape as the slalom
family and the native epilogue is `ret 0x18`. The runtime kind written by this
public constructor is `0x20`, matching the current decompile. The scratch builds
the fixed 70-sample double-slalom body with four straight samples at each end,
sinusoidal lateral motion, raised Y motion, orientation, deltas, strip mesh, and
`finalize_path_template`.

Residuals are expected. This is a semantic starter, not a tuned byte match.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 10.59% (129/683
candidate/target instructions) to 22.28% (574/683), with masked operands
improving from 12 ok, 0 unresolved, 5 mismatch to 31 ok, 0 unresolved, 1
mismatch.

2026-07-03 falloff shape: split the double-slalom center falloff into the two
native absolute-distance temporaries before the sine/scale multiply. Focused
Wibo moves from 22.28% (574/683) to 22.66% (588/683), with masked operands
improving from 31 ok, 0 unresolved, 1 mismatch to 32 ok, 0 unresolved, 1
mismatch.

2026-07-03 orientation guard: native source shape always dispatches the previous
sample through `rotate_matrix_world_z(roll_angle)` after the up/cross-vector
orientation frame. Removing the zero-roll guard moves focused Wibo from 22.66%
(588/683) to 22.84% (578/683), with masked operands unchanged at 32 ok,
0 unresolved, 1 mismatch.

2026-07-03 fixed-sample initializer spelling: reload primary and secondary X
from the stored primary `center_x` field, then delay the integer-to-float Z
conversion until inside the inlined sample initializer after the primary
identity call. Focused Wibo moves from 22.84% (578/683) to 23.14% (570/683);
the masked audit keeps the same single call mismatch but has one fewer audited
ok (31 ok, 0 unresolved, 1 mismatch).

Rejected: spelling the fixed trailing straight samples with `lead_out_start =
66` and `total_segments = lead_out_start + 4` regressed focused Wibo to 22.61%
(582/683) and worsened the masked audit to 30 ok, 0 unresolved, 2 mismatch, so
the fixed `70` / `66` constants stay in the scratch.

2026-07-03 retained mesh-face loop: replacing the direct `a`/`b` face writes
with the two-iteration `face_index` loop moves focused Wibo from 23.14% (570/683)
to 26.92% (580/683). Masked operands change from 31 ok, 0 unresolved,
1 mismatch to 32 ok, 0 unresolved, 3 mismatch; the extra residuals are in the
interior orientation call pairings.

Rejected: the `slalom` orientation scheduling split does not transfer here.
Expanding both lane orientations before either roll call reduced masked
residuals from 32 ok, 0 unresolved, 3 mismatch to 30 ok, 0 unresolved,
1 mismatch, but regressed focused Wibo from 26.92% (580/683) to 25.08%
(577/683). The compact helper calls stay as the better current score baseline.
