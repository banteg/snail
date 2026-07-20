# `initialize_looptheloop_path_template_pair` starter

This is an honest semantic starter for the path-template initializer at
`0x41b0f0`.

The scratch reconstructs the recovered loop-the-loop family setup from the IDA
and Binary Ninja decompiles: template metadata, primary/secondary samples,
straight approach/departure runs, the circular loop section, delta vectors,
strip-mesh vertices/faces, and the final `finalize_path_template` call.

It deliberately keeps the implementation source-level and plausible rather than
trying to force register allocation. Residuals are expected around helper
inlining, x87 scheduling, and the large mesh/face loops.

2026-07-03 ABI cleanup: focused diff shows the native tail is `ret 0x18`, so
the constructor uses the same six-argument stack cleanup as the surrounding path
template callsites. Updating the scratch and shared declaration from the stale
four-argument prototype moves focused Wibo from 35.59% (639/721) to 35.74%
(639/721), with masked operands unchanged at 39 ok, 0 unresolved, 0 mismatch.

2026-07-04 prologue order cleanup: the native entry compares `width_cells_`
against 4 and selects the loop wiggle before starting the `curve_source *
6.2831855f` integer conversion; it also writes `width_or_scale` after that
conversion. Delaying `PATH_CURVE_COUNT` and `width_or_scale` to match that
order keeps focused Wibo at 35.74% (639/721) but improves the masked audit from
39 ok to 40 ok, with 0 unresolved and 0 mismatch.

## 2026-07-15 ownership and source-shape recovery

The variant-0 builder now owns its fixed approach and departure samples
directly. The former `initialize_sample_pair` abstraction hid the native
indexed `AttachmentSample` writes, identity-transform calls, primary-center
copy, secondary Y offset, and per-sample unit length. Expanding those writes
also established that the departure center is grouped as the loop wiggle plus
`(4.0f - width * 0.5f)` and that the circular section updates `center_x` in two
steps.

The circular samples now build their actual orientation members in place:
fixed world-X right, normalized radial up, and a forward cross product. The
generated mesh likewise uses the recovered `Vector3` arithmetic rather than
three unrelated scalar stores. Keeping a real vertex temporary and assigning
`basis_right * lateral + position` recovers the native `0x54` stack frame.

The face grid retains the source family's do/while column traversal and its
parity-controlled duplicate texture calls. The two arms intentionally select
the same front or back texture: the target contains both branches and the same
residue is independently present in the Cage2 builder, so this is preserved as
authored source shape rather than collapsed as a semantic simplification.

Focused Wibo improves from 35.74% (639/721) to 64.75% (706/721), with a
9-instruction exact prefix and 46 masked operands ok, 0 unresolved, and 0
mismatch. A direct texture-call simplification briefly scored 66.01%, but was
rejected because it removes control flow proven by both the target and sibling
source-family evidence. Remaining differences are register allocation, x87
operation order, and local lifetime scheduling; none justify artificial
padding or volatile qualifiers.

## 2026-07-17 live owner and ABI closure

The restarted Binary Ninja database still carried the stale
`int32_t __thiscall(PathTemplate*, float, int32_t, char*, char*)` view. Native
`ret 0x18` cleanup and the refreshed `initialize_game_assets_and_world`
callsites independently prove six stack arguments after `this`: `curve_source`,
`width_cells_`, `side_exit`, `texture_a`, `texture_b`, and `cap_texture`.

A guarded repair now records the exact stale four-parameter annotation set,
the surviving stack-20 `arg5` annotation, and the absent stack-24 variable
before recreating the function as
`void __thiscall(Path*, float, int32_t, int32_t, char*, char*, char*)`.
Readback confirms every stack slot and the ordinary terminal
`finalize_path_template(self)` call. The two uniform API inputs are optimized
out in this constructor, but the caller evidence and callee cleanup retain
their ownership without inventing uses.

The source is unchanged by the metadata repair. Focused Wibo remains 64.47%
(706/721), with a 9-instruction exact prefix and 46 masked operands ok,
0 unresolved, 0 mismatch.

## 2026-07-20 path-lifetime ownership replay

Transactional Binary Ninja inspection recovered eleven complete register
lifetimes in the remaining builder body. The primary and secondary basis-right
vectors now render as `Vec3` owners both at initialization and at the later
cross-product reload. The two terminal delta records, ordinary and terminal
mesh vertices, and both complete facequad records likewise expose their real
owners instead of scalar or integer-pointer stores.

The replay verifies the canonical `Vec3`, `PathTemplateSample`, and
`ObjectFaceQuad` widths and key fields before applying the address-anchored
variables. Preview and exported readback both retain zero `__offset`
expressions. This is decompiler ownership recovery only: the honest scratch and
its 64.47% focused match remain unchanged.
