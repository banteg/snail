# initialize_start_path_template_pair

Ownership reconstruction for `initialize_start_path_template_pair @ 0x426400`.

The callsite passes six stack arguments and the native tail is `ret 0x18`.
Unlike the simpler terminal-row templates, this constructor allocates one extra
sample, decrements `segment_count`, and uses the final allocated sample directly
for the mesh row. The scratch models that allocation shape, the raised starting
plateau, the cosine descent, the flat tail, deltas, mesh, and finalization.

The retained scratch now matches 60.84% (603/610 candidate/target
instructions), with masked operands at 31 ok, 0 unresolved, 0 mismatch. The
candidate still has a 0x48 frame versus the target's 0x44 frame, so the
remaining mesh-row register ownership and prologue spill are still open.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 10.90% (124/610
candidate/target instructions) to 14.56% (530/610), with masked operands
improving from 8 ok, 0 unresolved, 6 mismatch to 23 ok, 0 unresolved, 2
mismatch.

2026-07-03 Phase B pass: spelling the allocation count through
`curve_segments + 15`, then setting `segment_count` from that local plus one,
matches the target's `add 0xf` / `inc` setup shape and shrinks the candidate
frame to `0x48`. Reloading primary and secondary X from the primary
`center_x` field instead of the constant argument then brings the final frame
to the native `0x44` and moves the focused matcher to 15.86% (525/610), with a
7-instruction prefix and masked operands at 19 ok, 0 unresolved, 2 mismatch.
An explicit count-of-11 tail loop was rejected: it made the tail counter look
more native but dropped the score to 15.63% and worsened the masked audit to
20 ok, 0 unresolved, 2 mismatch.

2026-07-03 Z-index helper spelling: keep the pair helper Z input as an integer
sample index and perform the int-to-float conversion inside the inlined helper
after primary identity. Focused Wibo moves from 15.86% (525/610) to 16.96%
(522/610), with masked operands improving from 19 ok, 0 unresolved, 2 mismatch
to 21 ok, 0 unresolved, 2 mismatch.

2026-07-03 lead-in Y lifetime rejection: spelling `radius + radius` as an
explicit `raised_y` local regresses focused Wibo from 16.96% (522/610) to
16.95% (523/610). The emitted code stores and reloads the doubled radius before
adding the secondary offset, while the current source keeps the x87 value live.
The source shape was reverted.

2026-07-03 direct sample-loop expansion: expanding the lead-in, flat tail, and
curved body samples to match the native direct setup removes the remaining
generic pair helper from the scratch. The retained shape stores primary X from
`center_x`, keeps the curved Z conversion before the cosine-derived Y, copies
the flat tail secondary Z from the written primary transform, and derives the
curved secondary Y from the written primary Y. Focused Wibo moves from 16.96%
(522/610) to 17.31% (511/610), with the 7-instruction prefix preserved and
masked operands improving from 21 ok, 0 unresolved, 2 mismatch to 22 ok,
0 unresolved, 2 mismatch. The remaining masked mismatches are still the
orientation calls aligned against the later strip-mesh allocation calls.

2026-07-03 raised-Y retry after direct loops: retesting the native-looking
`raised_y = radius + radius` local after direct sample-loop expansion still
regressed focused Wibo from 17.31% (511/610) to 17.02% (518/610). The
7-instruction prefix and masked audit stayed unchanged at 22 ok, 0 unresolved,
2 mismatch, so the inline `radius + radius` expression remains retained.

2026-07-03 retained mesh-face loop: replacing the direct `a`/`b` face writes
with a two-iteration `face_index` loop moves focused Wibo from 17.31% (511/610)
to 18.04% (521/610), with masked operands improving from 22 ok, 0 unresolved,
2 mismatch to 24 ok, 0 unresolved, 2 mismatch. This is an intentionally
qualified source-shape win: the previous 7-instruction prefix is lost and the
candidate frame grows from the native 0x44 to 0x48, so the prologue/register
lifetime debt remains open.

2026-07-03 tail-bound local rejection: replacing the flat tail upper bound
`curve_segments + 15` with the existing `last_segment_index` local regressed
focused Wibo from 18.04% (521/610) to 17.88% (520/610). The masked audit stayed
unchanged at 24 ok, 0 unresolved, 2 mismatch, so the direct expression remains
retained.

2026-07-03 neutral face-index lifetime probe: hoisting the mesh `face_index`
loop variable out of the `for` header, matching the spelling used by several
other path-template helpers, was exactly neutral at 18.04% (521/610). The
candidate frame stayed at 0x48 and the masked audit stayed at 24 ok, 0
unresolved, 2 mismatch, so the block-scoped loop variable remains.

2026-07-03 lead-in direct-index rejection: removing the primary/secondary
sample pointer locals from the first five-sample loop and spelling the writes
directly as `primary_samples[i]` / `secondary_samples[i]` regressed focused
Wibo from 18.04% (521/610) to 17.79% (537/610). The masked audit stayed at
24 ok, 0 unresolved, 2 mismatch, so the pointer locals remain retained.

2026-07-03 retained mesh-vertex staging: routing the row vertex calculation
through a local `Vector3 generated_position` before assigning `*vertex` matches
the native stack-spill shape better than direct component stores. Focused Wibo
moves from 18.04% (521/610) to 20.56% (528/610), and masked operands improve
from 24 ok, 0 unresolved, 2 mismatch to 26 ok, 0 unresolved, 2 mismatch. The
known prologue debt remains: candidate frame 0x48 versus native 0x44.

2026-07-04 retained mesh request-order cleanup: after mesh-vertex staging,
requesting facequads before vertices moves focused Wibo from 20.56% (528/610)
to 21.27% (528/610), and improves masked operands from 26 ok, 0 unresolved,
2 mismatch to 27 ok, 0 unresolved, 1 mismatch. The remaining mismatch still
pairs a native orientation call against the local mesh allocation call, so this
only narrows the allocation-call alignment debt.

2026-07-03 rejected curved byte-offset probe: replacing the curved body loop's
`primary_samples[sample_index]` / `secondary_samples[sample_index]` pointers
with an explicit `sample_offset` regressed focused Wibo from 20.56% to 18.72%
(528/610 to 533/610) and reduced the masked audit from 26 ok, 0 unresolved,
2 mismatch to 22 ok, 0 unresolved, 2 mismatch. Keep the indexed sample pointers
for the current `start` loop shape.

2026-07-04 retained tail-count retest: after mesh-vertex staging and the
facequads-first mesh request order, retesting the explicit count-of-11 flat-tail
loop now moves focused Wibo from 21.27% (528/610) to 21.65% (526/610). Masked
operands stay at 27 ok, 0 unresolved, 1 mismatch, and the prefix/frame debt
remains unchanged at candidate frame 0x48 versus native 0x44, so this is a
small current-shape win rather than a prologue fix.

2026-07-04 retained orientation scheduling expansion: spelling the curved-body
orientation work inline, with the first curved sample setting both previous
transforms to identity and later samples building primary and secondary
right-vector frames directly, moves focused Wibo from 21.65% (526/610) to
22.01% (526/610). Masked operands stay at 27 ok, 0 unresolved, 1 mismatch; the
remaining mismatch is still native orientation work aligned against the local
mesh allocation call.

2026-07-13 direct owner recovery: expanding both delta streams directly through
`Path::primary_samples` and `Path::secondary_samples` removes the remaining
scratch-local delta helper and moves the focused match to 25.39% (532/610).
The masked call audit becomes fully clean at 31 ok, 0 unresolved, 0 mismatch.
This is the same owner-level delta shape recovered independently in the
supertramp builder.

Windows instruction order confirms that the strip mesh requests vertices
before facequads: `(width_cells + 1) * (segment_count + 1)` is passed to the
vertex allocator first, followed by `2 * width_cells * segment_count` for
faces. Restoring that native order after the direct-delta recovery is both
source-correct and matcher-positive; the earlier 2026-07-04 facequads-first
result was a local alignment artifact and is superseded. Recovering the
owner-relative mesh row cursor and staging an explicit lateral offset then
moves the retained match to 25.65% (536/610).

Rejected after this ownership pass: rewriting only the five-sample lead-in or
only the curved body from their local primary/secondary pointers to direct
array expressions regressed the focused score. A do-loop spelling for the
already recovered two-face writer was byte-identical and was not retained.
Those loops remain explicit future ownership work rather than being forced to
share the supertramp spelling.

2026-07-15 coordinated sample-owner recovery: direct primary/secondary array
ownership across the raised lead-in, curved body, and flat tail combines with
separate logical Z counters to reproduce the native loop lifetimes. The lead-in
increments its sample and Z owners before writing the secondary delta; the
curve starts at sample 5 while retaining a zero-based `curve_index`; and the
tail starts at sample `curve_segments + 5` with its own Z owner. Keeping the
floating-point curve count live and reusing the incoming `length` argument slot
for the cosine radius also agrees with the target's stack ownership. Together
with the face and orientation recovery below, focused Wibo moves from 25.65%
(536/610) to 60.84% (603/610), while the masked call audit remains fully clean
at 31 ok, 0 unresolved, 0 mismatch.

The orientation source has a mixed ownership boundary. Two previous-sample
pointers own only the first curved sample's identity calls; the later vector
construction is authored through direct indexed arrays. Making all orientation
accesses direct regressed the focused result to 37.46% and introduced a masked
call mismatch. Keeping four current/previous pointers reached only 52.57%; one
previous pointer also regressed to 37.46%; and limiting pointers to the entire
identity branch reached 41.68%. The retained two-pointer/direct-vector shape is
the only probe that reaches 60.84% with the call audit clean.

The mesh face header interpretation above is superseded. The native first face
does not initialize its header in this loop. The reverse face writes the full
16-bit `header_word` value `4`; no stable semantic enum name has been recovered,
so the raw field/value remain intentionally unpromoted. Both parity branches
request the same texture reference. Their duplicated control flow and reversed
condition spelling are retained because the target contains both branches, not
to manufacture a semantic distinction that is absent from the binary.

Rejected or neutral during this pass: the face changes alone moved 25.65% to
24.16%, but became strongly positive as part of the coordinated ownership
cascade; reusing `length` for the radius moved 52.40% to 52.57%; a separate
curved `sample_index` regressed 60.84% to 58.81%; direct mesh-component float
stores regressed 60.84% to 59.88%; and mesh declaration/sample-offset ordering
was byte-neutral. Reversing the redundant parity condition and spelling the
curve guard as `curve_index < curve_segments` were score-neutral; both are
retained because they reflect the observed branch direction and logical owner.
The candidate frame remains 0x48 versus the target's 0x44.

## 2026-07-17 live constructor ABI closure

The restarted Binary Ninja session confirms the native `retn 0x18` contract:
`Path* self`, `float length`, integer width and side-exit mode, two surface
textures, and the Windows-only cap texture. This agrees with the portable iOS
`cRPath::BuildStart(float, int, bool, char*, char*)` prefix. The stale database
prototype had only three stack arguments, shifted the first texture into the
mode slot, and omitted the final three arguments.

Guarded recreation and post-write readback now report the exact seven-parameter
prototype with no pending operation. The refreshed callee exposes `Path` fields
and void finalizer flow, while both initializer callsites use the primary and
secondary `Path` owners with all six stack operands. This is analysis-only:
focused matching remains 60.84% (603/610) with 31 clean masked operands.

2026-07-20 live mesh-owner closure: the separately previewed start schedule
recovers the primary curved sample, both previous-sample right vectors, both
current-sample cross-product reloads, the primary mesh sample, each generated
`Vec3` vertex, and the two complete facequad records. The intermediate
secondary current-sample cursor stays automatic because typing its negative
byte-relative accesses made the decompile less exact. All nine retained owners
render direct fields and introduce no `__offset` expression. This is
analysis-only: focused matching remains 60.84% (603/610), with 31 clean masked
operands.
