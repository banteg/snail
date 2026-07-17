# initialize_supertramp_path_template_pair

Ownership reconstruction for
`initialize_supertramp_path_template_pair @ 0x423f10`.

The native tail is `ret 0x1c`, matching seven explicit stack arguments. This
constructor allocates an extra sample before decrementing `segment_count`, then
uses the final allocated sample directly in the mesh. The scratch models the
flat approach, circular supertramp arc, separate secondary radius, direct mesh
rows, deltas, and finalization.

The retained scratch now matches 51.62% (529/552 candidate/target
instructions), with a 15-instruction exact prefix, an exact 0x2c stack frame,
and masked operands at 32 ok, 0 unresolved, 0 mismatch. Residuals are primarily
register allocation and store scheduling; this is not an exact match.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 8.62% (144/552
candidate/target instructions) to 15.61% (473/552), with masked operands
improving from 4 ok, 0 unresolved, 6 mismatch to 23 ok, 0 unresolved, 4
mismatch.

2026-07-03 arc schedule cleanup: native initializes both primary and secondary
arc sample positions before orienting either sample. Moving primary orientation
after the secondary position writes and reloading secondary X from the written
primary `center_x` moves focused Wibo from 15.61% to 16.20% (473/552 unchanged),
shrinks the candidate stack frame from 0x48 to 0x44, and improves masked
operands from 23 ok, 0 unresolved, 4 mismatch to 25 ok, 0 unresolved, 2
mismatch.

2026-07-03 Z-index helper spelling: keep the flat lead-in pair helper Z input
as an integer sample index and perform the int-to-float conversion inside the
inlined helper after primary identity. Focused Wibo moves from 16.20% to
16.59% (473/552 unchanged), with masked operands unchanged at 25 ok, 0
unresolved, 2 mismatch.

2026-07-03 allocation-count spelling: materializing
`last_segment_index = curve_segments + 7`, then deriving `segment_count` from
that local, matches the target's `add 0x7` / `inc` count setup. Focused Wibo
moves from 16.59% (473/552) to 16.96% (474/552), with masked operands improving
from 25 ok, 0 unresolved, 2 mismatch to 26 ok, 0 unresolved, 1 mismatch.
Rejected adjacent probe: reloading flat lead-in helper X from the written
primary `center_x` regressed the focused score to 16.75% (475/552) and restored
the two masked mismatches, so the flat helper keeps the constant X argument.

Rejected: materializing a separate `curve_segments_f` float local for both
radius and angle division, like the decompiler's stored float count, was exactly
neutral at 16.96% (474/552) with masked operands unchanged at 26 ok,
0 unresolved, 1 mismatch. The shorter direct casts remain retained.

2026-07-03 rejected facequad inner-loop probe: unlike `sweep`/`snake` and the
twister twins, replacing the direct `a`/`b` facequad writes with a two-iteration
`face_index` loop regressed focused Wibo from 16.96% (474/552) to 10.19%
(488/552), and regressed the masked audit from 26 ok, 0 unresolved, 1 mismatch
to 7 ok, 0 unresolved, 3 mismatch. The cap-texture mesh keeps the direct
facequad writes for now.

2026-07-03 neutral flat lead-in expansion: expanding the seven flat lead-in
samples out of `initialize_pair_sample`, while keeping the earlier rejected
`center_x` reload out, was exactly neutral at 16.96% (474/552), with masked
operands unchanged at 26 ok, 0 unresolved, 1 mismatch. The helper-routed source
stays retained until a non-neutral lifetime lead appears.

2026-07-03 rejected arc-loop scalar probes: removing the arc secondary sample's
scalar-field writes regressed focused Wibo from 16.96% (474/552) to 16.49%
(467/552) and worsened the masked audit to 22 ok, 0 unresolved, 2 mismatch.
Reloading arc primary transform X from `primary->center_x`, matching the
decompiler spelling, also regressed to 16.76% (474/552) with 25 ok,
0 unresolved, 2 mismatch. The retained arc loop keeps those scalar writes and
the constant primary X store.

2026-07-03 retained mesh-vertex staging: like `start`, routing the row vertex
calculation through a local `Vector3 generated_position` before assigning
`*vertex` improves the focused matcher from 16.96% (474/552) to 17.10%
(477/552). The masked audit stays at 26 ok, 0 unresolved, 1 mismatch, and the
cap-texture facequad writes remain direct because the earlier two-iteration
`face_index` probe regressed sharply.

2026-07-04 retained mesh request-order cleanup: after mesh-vertex staging,
requesting facequads before vertices moves focused Wibo from 17.10% (477/552)
to 18.66% (477/552), and improves masked operands from 26 ok, 0 unresolved,
1 mismatch to 27 ok, 0 unresolved, 1 mismatch. The remaining mismatch still
pairs a native orientation call against the local mesh allocation call, so the
cap-texture face writer and larger frame residual stay explicit.

2026-07-03 neutral ownership retests after mesh-vertex staging: re-expanding
the seven flat lead-in samples out of `initialize_pair_sample` remained exactly
neutral at 17.10% (477/552), with masked operands unchanged at 26 ok,
0 unresolved, 1 mismatch. Rewriting the arc loop to address samples through an
explicit byte offset was also neutral at 17.10% (477/552) with the same masked
audit. Keep the helper-routed lead-in and indexed arc pointers until a
non-neutral lifetime lead appears.

2026-07-04 post-request-order arc ownership retest: rewriting the arc loop to
address primary/secondary samples through an explicit byte offset remains
exactly neutral after the facequads-first allocation cleanup. Focused Wibo stays
18.66% (477/552), with masked operands unchanged at 27 ok, 0 unresolved,
1 mismatch, so the indexed arc pointers remain retained.

2026-07-04 rejected direct-orientation expansion: spelling the arc orientation
inline with direct `basis_right` / `basis_up` component stores, instead of
calling the retained local helper, regressed focused Wibo from 18.66% (477/552)
to 17.98% (449/552). Masked operands worsened from 27 ok, 0 unresolved,
1 mismatch to 20 ok, 0 unresolved, 3 mismatch, so the helper-routed orientation
stays retained.

2026-07-13 ownership cascade: the earlier isolated probes above were retested
after recovering the surrounding owner-relative source shape. Expanding the
flat lead-in, indexing the arc directly through `Path::primary_samples` and
`Path::secondary_samples`, spelling both orientation passes directly, and
computing both delta streams in the owner all became strongly positive as a
group. The focused match moved from 18.66% to 43.49%, candidate size from 477
to 538 instructions, the exact prefix from 0 to 15 instructions, and the stack
frame from 0x44 to the target's 0x2c. This supersedes the context-specific
isolated rejections above; no register forcing, padding, barriers, or other
fakematching is present.

The same pass recovered the mesh as two native nested loops: an owner-relative
sample-row cursor for vertices and a two-iteration front/back face loop for
each cell. Vertex allocation precedes face allocation, face headers are cleared
with the full `header_word`, and the generated vertex is staged as a lateral
offset plus the sample position. The face writer retains the apparently
redundant checkerboard branches because the same authored source-family shape
appears in the halfpipe and cage2 builders and is present in the Windows
control flow.

Windows operand tracing also resolves the seven stack arguments. Argument 4
owns the front texture, argument 5 owns the back texture, argument 6 is unused,
and argument 7 owns the terminal cap texture. Both front parity arms select
argument 4, both back parity arms select argument 5, and only the final row's
front face selects argument 7. The shared `Path` declaration now records those
owners as `texture_a`, `texture_b`, `unused_texture`, and `cap_texture`.

2026-07-15 arc ownership follow-up: the native curved section does not write
the secondary sample's five scalar fields before initializing its transform.
Removing those stale scratch stores first moves focused Wibo from 43.49%
(538/552) to 45.00% (528/552). Reloading primary position X from the authored
`center_x` field, as the target does, then realigns the arc calls and reaches
51.39% (530/552), while clearing the old call mismatch and producing 31 ok,
0 unresolved, 0 mismatch.

The target guards the circular arc before deriving its secondary radius and
owns a post-tested logical curve loop. Recovering that guard and `do/while`
reaches 51.43% (529/552) and 32 clean audited operands. Materializing the
shared floating curve count is codegen-neutral but retained because the target
uses the same value for both radius construction and angle division. Finally,
placing the flat lead-in Z conversion after the target-backed center-X reload
reaches 51.62% (529/552), with the 15-instruction prefix and exact 0x2c frame
preserved. This supersedes the pre-cascade secondary-scalar and center-X probe
results above; all retained changes now agree with both current decompilers.

## 2026-07-17 constructor ABI closure

The native tail returns with `retn 0x1c`, and both world-initializer
constructions visibly push the complete Windows contract: float length,
integer width and side mode, front/back textures, an ABI-owned unused texture,
and the terminal cap texture. Guarded Binary Ninja recreation and readback now
recover that exact void `Path*` member ABI, including the two formerly hidden
texture slots.

iOS exposes a seven-argument `BuildSuperTramp(float, float, int, bool, char*,
char*, char*)` sibling, but its scalar/texture split differs from Windows. The
Windows pushes and callee dataflow therefore remain authoritative here rather
than forcing the portable signature onto this build. This closure is
analysis-only: focused Wibo remains 51.62% (529/552), with a 15-instruction
prefix and 32 clean masked operands.
