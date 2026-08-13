# initialize_start_path_template_pair

Current recovery: incomplete (`analysis,compiler` residuals). The verified
Android/iOS builder bodies establish the portable sample/control graph, and
the live Windows body covers the native mesh/face tail, but current-state
retests have disproved the former compiler-only classification. All references
are clean; remaining differences still include recoverable owner lifetimes and
source scheduling as well as compiler layout.

Ownership reconstruction for `initialize_start_path_template_pair @ 0x426400`.

The callsite passes six stack arguments and the native tail is `ret 0x18`.
Unlike the simpler terminal-row templates, this constructor allocates one extra
sample, decrements `segment_count`, and uses the final allocated sample directly
for the mesh row. The scratch models that allocation shape, the raised starting
plateau, the cosine descent, the flat tail, deltas, mesh, and finalization.

The retained scratch now matches 87.94% at 609/610 candidate/target
instructions, with a 148-instruction exact prefix and masked operands at 35
ok, 0 unresolved, 0 mismatch, 0 unaudited. The candidate frame agrees with
the target at 0x44, and the mesh setup now snapshots both native banks before
using a separate row/sample induction. The face pass now also resets its
two-face counter at the native column boundary; branch-local record address
formation remains open.

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

2026-07-26 branch-local UV completion: the native front and back paths end
independently at `0x426ba7` and `0x426c5e`; each writes its own
`face->uv[3].v` before rejoining the two-face loop. Recovering those authored
branch-local writes raises focused Wibo from 60.84% to 63.70% (603 to 605
candidate instructions) and expands the clean operand audit from 31 to 33,
with no unresolved or mismatched operands.

Unlike Supertramp and the loop family, moving Start's face pointer and whole
record lifetime into the two branches regresses the focused result to 54.72%.
That probe does shrink the candidate frame from 0x48 to the native 0x44, but
it also disrupts the proven register schedule across the constructor. It is
rejected rather than treating frame parity as sufficient evidence. Moving the
mesh vertex destination below the generated-position temporary is
byte-neutral and is likewise not retained.

## 2026-07-27 paired mobile boolean ownership

The exact Android and iOS symbols both name
`cRPath::BuildStart(float, int, bool, char*, char*)`, independently proving
that the third authored scalar is `bool side_exit`. Windows keeps the same
four-byte stack slot and adds its trailing cap texture, so refining the source,
shared headers, and live Binary Ninja prototype is ABI- and byte-neutral:
focused matching remains 63.70% (605/610) with 35 clean masked operands.

The mobile bodies also test the logical curve index for their first curved
sample. That source spelling is not portable back to the VC6 build: replacing
the native-equivalent `i <= 5` guard with `curve_index == 0` changes the frame
and register schedule and regresses focused agreement to 44.99% (608/610).
The probe is rejected; mobile evidence closes the boolean owner without
overriding the independently measured Windows control shape.

## 2026-07-28 paired-mobile control ownership

The exact Android
`analysis/decompile/android/functions/0005379c-_ZN6cRPath10BuildStartEfibPcS0_.c`
and iOS
`analysis/decompile/ios/functions/0005edd0-_ZN6cRPath10BuildStartEfibPcS0_.c`
bodies independently preserve the portable five-sample lead, eleven-sample
tail, cosine middle, adjacent-sample orientation, and final
delta/`CalcLengthZ` passes. Windows remains authoritative for exact definition
identities, `0xa8` sample-byte cursors, the six-argument ABI, and its
native-only cap-texture/strip-mesh tail.

A transactional Binary Ninja replay now records 14 exact Windows owners: four
isolated stack values plus ten merged definition clusters covering the curve
count and radius, lead and tail indices/offsets, curved-sample index/offset,
and delta index/offset. The preview changed every proposed owner, rolled the
split clusters back before application, and introduced no `__offset`
expression. Live readback renders the distinct loops directly, and a second
replay found every operation already current.

This is analysis-only. Focused Windows matching remains honestly **63.70%**,
**605/610** candidate instructions, a zero-instruction exact prefix, and 35
accepted masked operands with no unresolved, mismatched, or unaudited
operands. No source expression or matcher exception changed.

## 2026-07-30 terminal-delta subtraction bound

The exact two-site `Vector3::operator-` plan from the neighboring path
constructors compiles byte-identically here. Both isolated replacements and
their combination leave 63.70%, 605/610 instructions, prefix 0/610, and all 35
clean references unchanged. Start retains its expanded component spelling and
records the exhaustive neutral bound.

## 2026-07-30 mesh arithmetic bound

The native unbranched mesh block at `0x4269e2..0x426a50` keeps the lateral
value live in x87 form. Recasting the source local as `double` loses 56.01
weighted bytes; spelling the whole expression in double loses 59.66 weighted
bytes and adds reference debt, while a volatile float loses 11.17. Splitting
the existing float expression is byte-identical.

The `Vector3` add and scale operators were then tested alone and together.
Every form is byte-identical, so Start retains its component arithmetic at
**63.70%**, **605/610** instructions, prefix 0/610, and 35 clean references.
This exhausts the bounded arithmetic family without a source edit.

## 2026-07-30 branch-local grid dependency bound

The earlier rejected branch-local face lifetime was expanded into its adjacent
grid and orientation dependencies. Splitting face row and column owners around
the two branch-local records falls from the retained **63.70%** to **52.77%**
(618/610), with prefix 7/610 and all 35 references clean. Giving the vertex
grid separate owners is byte-identical to that result, so it does not recover
the native cyclic EBP/EBX/EDI assignment.

Replacing the two previous-sample aliases with direct identity callsite
addresses in the same exact-frame variant falls further to **50.45%**
(615/610). The simpler branch-local face probe remains **54.72%** (618/610):
it reaches the native `0x44` frame, but none of the dependency-complete
variants restores whole-function agreement. Start therefore keeps its shared
face owner and `0x48` frame; frame parity alone is not sufficient evidence for
a lower-agreement rewrite.

## 2026-07-30 curved byte-cursor transfer rejected

Windows begins Start's curved body with byte offset `0x348` at `0x42664a`,
uses the offset independently from the logical sample and curve indices, and
advances it by `0xa8` at `0x4268a2`. Replaying that direct current/previous
sample cursor across both lanes after the coordinated sample-owner cascade is
still negative: it loses 68.42 weighted bytes, falls from **63.70%** to
**60.63%**, and shortens the candidate from 605 to 604 instructions. The
zero-length exact prefix and all 35 references are unchanged.

The probe is recorded and reverted. As with Turnunder, the native byte
induction remains compiler-derived in the retained source context; Start's
mixed identity-pointer/direct-orientation boundary is not replaced by a
locally plausible cursor that reduces whole-function agreement.

## 2026-07-30 isolated grid and curve-control ownership

Live Windows MLIL separates the strip-mesh phases exactly as the retained
source now does: the vertex phase owns `row` and `column`, while the face phase
starts fresh row and column counters. Isolating only that source boundary moves
focused matching from 63.70% to 63.87%, adding 3.66 weighted bytes with the
candidate unchanged at 605/610 instructions and all 35 masked references
clean. Reusing the vertex counters in the face phase reverses the gain exactly.
The earlier coupled grid/face-record rejection therefore does not reject the
grid boundary; its regression came from moving the whole face record into the
branches.

The native vertex phase also initializes its physical sample offset only after
the non-negative segment guard. Moving the declaration to that proven scope is
byte-neutral, as is moving the zeroed curve index inside its positive-count
guard. The retained pre-guard curve-index spelling follows Windows MLIL and
keeps the logical owner explicit. Moving both previous-sample pointers into
the identity branch is not a frame fix: from the final baseline it regresses
to 44.74% (606/610) despite keeping all references clean. Swapping the
identity/orientation source arms likewise regressed the earlier 63.70%
baseline to 59.52% (603/610), so the current control spelling remains.

Windows implements the five-sample lead phase with separate logical and
`0xa8` byte cursors, but forcing that physical cursor into the C++ source
regresses 63.87% to 62.06% at the same 605 candidate instructions. This is a
compiler-derived loop owner rather than an authored source boundary; direct
indexed arrays remain retained. The remaining 0x48-versus-0x44 frame
difference is bounded to the cross-branch orientation allocation schedule and
is not being forced through source-shape regressions.

## 2026-07-31 direct face-offset record ownership

Start's existing single face pointer still extended one address owner across
both winding branches. Replacing it with a semantic integer offset and direct
facequad array writes raises focused matching from **63.87%** to **74.73%**,
extends the exact prefix from 0 to 122 instructions, and moves candidate size
from 605 to 613 against the 610-instruction target. All 35 references remain
clean.

This result is compatible with the existing direct sample-array ownership and
does not revive the separately rejected branch-local pointer/frame variants.

## 2026-07-31 direct vertex-index boundary

Replacing Start's shared mesh-vertex pointer with an integer index and direct
array writes is exactly byte-neutral at **74.73%**, 613/610 instructions,
prefix 122/610, and 35 clean references. No source edit is retained. Together
with the sharply negative Snake result, this bounds the adjacent vertex-owner
transfer rather than treating the face-record gain as a blanket array-access
rule.

## 2026-07-31 post-face ordinary position ownership

The complete mesh arithmetic grid was replayed after direct face ownership
changed the whole-function allocation. The ordinary authored
`Vector3::operator+`, previously neutral, now adds **3.64 weighted bytes** and
raises Start from **74.73% to 74.90%**. Candidate/target size remains 613/610,
prefix remains 122/610, and all 35 references remain clean. A reverse probe
reproduces the 74.73% predecessor.

The neighboring forms remain closed. Member scaling alone falls to 73.37%;
pairing it with the addition reaches only 73.53%; and all four alternate
lateral owners lose 30–49 weighted bytes and shorten the prefix to 68. The
retained position add is therefore the only positive post-face arithmetic
owner.

## 2026-07-31 post-face mesh/face counter reuse

Direct face records changed the allocation dependency behind the earlier
separate-grid result. Reusing only the mesh row in the face pass is
byte-identical, while reusing the mesh column adds **36.35 weighted bytes**.
Reusing both counters is the unique winner, adding **43.62 weighted bytes**
and raising focused matching from **74.90%** to **76.86%**.

The retained shared-counter source keeps candidate/target size at 613/610,
prefix at 122/610, and all 35 references clean. A complete reverse probe
restores the 74.90% predecessor. The native SSA names split the post-reset
lifetimes, but do not prove distinct authored declarations; the paired
dependency result and the family-wide reused-loop idiom support one source
row/column pair reset between phases.

The updated frontier is bounded again. All four vertices/facequads declaration
and load orders are byte-identical. The member scale operator is also neutral.
Split-float lateral arithmetic is neutral, while double and volatile forms
lose 15–55 weighted bytes and the double expression adds reference debt. The
retained result is **76.86%**, 613/610 instructions, prefix 122/610, with all
35 references clean.

## 2026-08-13 current-state curve ownership recovery

The former `semantic-complete` / compiler-only classification was stale. It
was based on probes made before direct face ownership, shared mesh/face
counters, and the current vector arithmetic changed VC6's whole-function
allocation. Replaying the previously rejected curve owners against that new
frontier recovers several ordinary authored boundaries.

First, the identity pointers belong only to the first-curve-sample arm. The
native and paired mobile bodies make later-sample orientation the fallthrough
path, while the first sample branches forward to the two `RotIdentity` calls.
Moving the previous-sample aliases into that arm, reversing the branch, and
testing the logical `curve_index` owner raises the focused match from 76.86%
to 77.74% without reference debt. This supersedes the July 27 conclusion that
the mobile logical-index spelling was not portable to the Windows build.

Both orientation lanes use the shared authored `tVector::operator-` operation.
Either lane alone is byte-neutral, but the paired replacement adds 36 fuzzy
bytes and reaches 79.38%. Replaying the same authored subtraction at the two
terminal delta lanes adds another 27 fuzzy bytes, raises the match to 80.59%,
and extends the exact prefix from 122 to 145 instructions. The old neutral
terminal-delta result is therefore allocation-state-specific, not an exhausted
semantic result.

Windows forms the secondary previous-sample address only after returning from
the primary identity call. Narrowing that pointer to its callsite removes the
candidate spill; a reverse sweep loses 28 fuzzy bytes. Keeping the logical
counter increment before the physical sample advance and spelling the later
sample test as `curve_index != 0` then reaches exact candidate/target size and
extends the prefix to 148 instructions. Positive-index spellings have a higher
raw fuzzy score (83.02%) but regress the prefix to 145 and leave the candidate
one instruction short, so they are rejected as score-only tradeoffs.

The retained frontier is **82.46%**, **610/610** instructions, prefix
**148/610**, and 35 clean references. Because multiple allegedly exhausted
source owners produced material current-state gains, the scratch metadata is
corrected to `incomplete` with `analysis,compiler` residuals.

## 2026-08-13 live mesh row ownership

The reopened Windows database confirms the native mesh setup at
`0x4269b1`: it snapshots `object->vertices` and `object->facequads`, initializes
the logical row to zero, and advances a separate primary-sample byte cursor by
`0xa8` after each row. The old scratch instead carried an explicit
`sample_offset` alongside `row`; in the current allocation state VC6 spilled
that cursor and retained a mesh bank in `EBX`.

Deriving the row sample directly as `&primary_samples[row]` lets VC6 recover
the native `EBX += 0xa8` induction while keeping the authored `Object*`, vertex
bank, and facequad bank snapshots explicit. Focused matching rises from
**82.46%** to **84.75%**, with exact **610/610** instruction count, the
**148/610** prefix, and all 35 references preserved.

Two higher-score shapes remain rejected as tradeoffs. Reading vertices back
through the mesh object reaches 85.81% but contradicts the live bank snapshot
and leaves the candidate one instruction short. Testing the curve's physical
sample displacement reproduces the native `cmp edi, 0x348`, but currently
disturbs the preheader and also loses an instruction. Those observations are
useful combination leads, not retained source yet.

## 2026-08-13 live face-counter ownership

The reopened Windows body resets the two-face counter at `0x426acc`, before it
stores the next column and derives the two U coordinates. The previous scratch
declared and initialized that counter in the inner `for` header after the U
values, extending the column arithmetic across the wrong owner boundary.

Moving only the counter initialization ahead of the U-coordinate derivation
reproduces the native EDX/ECX setup and raises focused matching from **84.75%**
to **87.94%**. The exact prefix remains **148/610** and all 35 masked references
remain clean. VC6 now emits 609 candidate instructions against 610 native
instructions because it hoists the common face-record scale before the winding
branch; Windows forms that scale independently in each arm.

The adjacent ownership hypotheses are bounded rather than forced. Branch-local
face pointers sharply regress. Two branch-scoped integer offsets fall to
74.30%, and one shared offset assigned independently by both arms falls to
75.18%; both disturb owners from the function prologue onward. A `switch`
restores exact instruction count and reaches 88.69%, but reverses the native
branch orientation and conflicts with the family-wide authored `if` shape, so
it is rejected as a score-only rewrite. `if (!face_index)` and `do`/`while`
spellings are byte-identical to the retained form. The native counter boundary
is retained; the branch-local scale remains an explicit analysis residual.
