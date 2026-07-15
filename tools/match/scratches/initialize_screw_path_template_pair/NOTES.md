# `initialize_screw_path_template_pair` starter

This is an honest semantic starter for the path-template initializer at
`0x41eda0`.

It reconstructs the screw template setup, three-sample entrance, five-sample
exit, helical middle section, recovered `rotation_scalar_94` angle, rotated
secondary lane, adjacent-sample orientation, deltas, strip mesh, and final
template pass.

The scratch is partial and keeps the source plausible. Any future tightening
should focus on real lifetime/control-flow shape.

2026-07-03 ABI cleanup: the constructor callsite passes six stack arguments
(`curve_count`, `width_cells`, an unused mode, two textures, and a cap texture)
and the native tail is `ret 0x18`. Updating the scratch and shared declaration
from the stale four-argument prototype moves focused Wibo from 18.80% (613/685)
to 18.95% (613/685), with masked operands unchanged at 19 ok, 0 unresolved, 4
mismatch.

2026-07-03 sample setup lifetime pass: the screw-only entrance, exit, and
helical middle loops now spell the native sample setup directly instead of
calling the generic sample-pair helper. The retained shape delays the Z counter
conversion until after primary identity, removes the helper's extra helical
secondary-X store, and computes the previous-sample up-vector cosine before the
negated sine. Focused Wibo moves from 18.95% (613/685) to 30.95% (601/685),
with the masked audit improving from 19 ok, 0 unresolved, 4 mismatch to 33 ok,
0 unresolved, 0 mismatch.

2026-07-04 header schedule probe rejected: moving the mirror/side/scale header
writes into the active screw branch so `width_cells`, `kind`, and segment-count
setup precede them matched the native-looking entry order more closely, but was
metric-neutral at 30.95% (601/685) with the masked audit unchanged at 33 ok, 0
unresolved, 0 mismatch. The scratch keeps the shared header spelling rather
than adding branch-local boilerplate without a matcher win.

2026-07-15 mesh ownership recovery: the native face builder preserves parity
branches even though both arms of each orientation currently request the same
texture, advances face columns with a `do/while`, and materializes an ordinary
row position as a `Vector3` before storing it. Recovering those source facts
raises focused Wibo from 30.95% (601/685) to 39.88% (619/685), with 32 clean
masked operands and no unresolved or mismatched operands. The parity branches
provide the largest independently measured gain, reaching 39.41% (614/685);
the face-column lifetime then reaches 39.78% (612/685).

2026-07-15 rejected lifetime probes: an explicit byte cursor for the
three-sample entrance regressed focused Wibo to 39.63% (617/685), and direct
array-member spelling regressed it to 39.21% (631/685) while introducing a
masked call mismatch. An explicit helical byte cursor fell to 33.18% (617/685)
with four call mismatches; separately duplicating the secondary up-vector trig
calls fell to 26.77% (630/685) with one call mismatch. A mutating five-sample
departure loop remained audit-clean but regressed to 39.72% (619/685). These
forms are not retained until the surrounding orientation lifetimes explain the
native schedule as a whole.
