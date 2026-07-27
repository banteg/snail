# `initialize_looptheloop_path_template_pair` starter

This is an honest semantic starter for the path-template initializer at
`0x41b0f0`.

The scratch reconstructs the recovered loop-the-loop family setup from the IDA
and Binary Ninja decompiles: template metadata, primary/secondary samples,
straight approach/departure runs, the circular loop section, delta vectors,
strip-mesh vertices/faces, and the final `calc_path_length_z` call.

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
`calc_path_length_z(self)` call. The two uniform API inputs are optimized
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

## 2026-07-26 complete mesh ownership

Raw native instructions at `0x41b7ad..0x41b8b8` close the values behind the
previously typed mesh sample and vertex. The ordinary branch owns a lateral
offset and generated position before materializing its destination vertex. The
terminal branch independently owns its lateral offset, the previous sample's
endpoint with the Z lane extended by `1.0f`, a generated position, and its
branch-local destination vertex.

The face loop at `0x41b98b..0x41bae2` likewise materializes separate complete
front and back records. Each branch owns its face pointer, 16-bit header clear,
indices, redundant parity-selected texture call, and all four UV pairs. The
coupled owner recovery raises focused matching from 64.47% (706/721) to 69.43%
(725/721), adds a clean masked operand for 47 ok with no unresolved or
mismatched operands, and preserves the exact native `0x54` frame.

A follow-up spelling through the shared by-value `Vector3` arithmetic operators
regressed the focused result to 67.17% (723/721). The retained explicit vector
owners follow the native branch-local lifetime evidence without forcing its
register schedule.

## 2026-07-26 mobile-backed initializer order

The exact iOS `cRPath::BuildLoopTheLoop(float, int, bool, char*, char*)` body
retains the redundant kind-0 assignment in the width-4 branch, while Android
independently confirms the same base kind and width-4 wiggle selection. The
Windows target stores its initial kind before materializing the zero-valued
wiggle local; the shared variant-0 skeleton had declared that local first.

Moving the ordinary kind assignment ahead of the local declaration recovers
that natural source order. Focused matching rises from 69.43% to 69.71%
(725/721), and the exact prefix expands from 9 to 22 instructions with all 49
masked operands clean. An explicit `curve_count + 14` owner and the mobile
taper-expression grouping were tested separately and rejected because they
regressed the Windows build to 66.90% and 65.14%, respectively.

## 2026-07-27 authored boolean ABI

The exact Android and iOS symbols independently spell the third argument as
`bool`. The shared matcher declaration, guarded Binary Ninja refinement, IDA
type replay, and repair fallback now agree on `bool side_exit` instead of a
generic `int32_t`. The parameter is unused in this body, so the correction is
code-generation neutral and focused matching remains honestly at 69.71%.

Windows still cleans six stack arguments and its callers supply one trailing
texture beyond the five-argument mobile method. That platform-specific input
is retained rather than deleting a proven Windows ABI slot.
