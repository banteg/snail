# initialize_wibble_path_template_pair

Ownership reconstruction for `initialize_wibble_path_template_pair @ 0x4289a0`.

Captures the fixed 32-sample wibble template: endpoint samples, sinusoidal
interior up-vector wobble, secondary sample offset, delta recomputation,
generated strip mesh, and finalization.

Current focused result: 55.68% (545/608 candidate/target instructions), with
35 masked operands ok, 0 unresolved, and 0 mismatched. The remaining mismatch
is source-shape/codegen debt, especially the native stack frame, pointer-shaped
loop counters, delta recomputation, and shared mesh tail. No dummy symbols,
inline assembly, flag changes, or volatile/register games were introduced.

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

2026-07-13 lane ownership: the native interior loop copies exactly the
0x40-byte `TransformMatrix` from each primary sample to its secondary peer;
the scalar fields at offsets `+0x90..+0xa0` remain primary-owned. Removing the
five scratch-only scalar copies moves focused Wibo from 31.86% (522/608) to
35.27% (492/608), with the masked audit still clean at 29 ok, 0 unresolved,
0 mismatch. Recovering the independently initialized primary and secondary
endpoint transforms and their `delta_length = 1.0f` stores moves it further to
36.48% (483/608), with 27 ok, 0 unresolved, 0 mismatch.

2026-07-13 interior orientation ownership: after constructing each primary
sample's up vector, the native loop derives `basis_forward` from the current
position minus the previous primary position, normalizes it, and derives
`basis_right` as `basis_up` cross `basis_forward` before copying the transform
to the secondary lane. Restoring that chain moves focused Wibo from 36.48%
(483/608) to 37.50% (512/608), with the masked audit still clean at 28 ok,
0 unresolved, 0 mismatch.

2026-07-15 sample ownership cascade: expanding the endpoint and interior
sample initializer calls into their directly owned `PathSample` stores recovers
the native endpoint scalar/identity sequence and the split interior
`sample_index`/`local_index` traversal. The interpolated center remains sample
metadata while transform X stays zero, and only the 0x40-byte transform is
copied into the secondary lane before its basis-up offset. Materializing
`roll_phase` before those sample stores preserves the already-evidenced native
trigonometric schedule; leaving it after the stores scored 55.16% but introduced
a `3.0f`/`0.20943952f` operand mismatch. The retained form moves focused Wibo
from 37.50% (512/608) to 55.68% (545/608), with the masked audit improving from
28 to 35 ok and remaining at 0 unresolved, 0 mismatch.

2026-07-15 face-header ownership: the mesh face initializer clears the full
16-bit `header_word`, not merely the low-byte flag view. Naming the owning field
makes that width explicit without changing the generated store.

## 2026-07-17 live constructor ABI closure

Live callsite disassembly shows the six stack arguments in order: `6.0f`, width
`8`, mode `1`, two surface textures, and the vertical texture. The native tail
at `0x429235` is `retn 0x18`, correcting the stale `ret 0x1c` scratch banner,
and the portable iOS symbol independently preserves
`cRPath::BuildWibble(float, int, bool, char*, char*)`.

Guarded recreation and post-write readback now expose the complete seven-
parameter `Path*` prototype with no pending operation. The refreshed caller
uses `path_pairs[0x28].primary` with all six stack operands, and the callee now
ends in void finalizer flow. This is analysis-only: focused matching remains
55.68% (545/608) with 35 clean masked operands.

## 2026-07-20 live lifetime ownership

A guarded transaction proves ten complete live owners: the primary seed,
up/right vectors, secondary position, both terminal deltas, mesh sample and
vertex, and both face records. Their accesses now render through
`PathTemplateSample`, `Vec3`, and `ObjectFaceQuad`. The constructor retains its
16 existing fixed-index `__offset` occurrences for samples 30/31, but the
replay adds none. Focused matching remains 55.68% (545/608) with 35 clean
masked operands.
