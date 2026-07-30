# initialize_turnover_path_template_pair

Ownership recovery for `initialize_turnover_path_template_pair @ 0x426cb0`.

The constructor callsite and target tail show six stack arguments (`ret 0x18`).
The retained scratch scores 52.22% (612/671 candidate/target instructions),
with 36 masked operands clean, 0 unresolved, and 0 mismatch. It now owns the
straight sample seeds, curved sample construction, transform propagation, and
16-bit face header. The main remaining structural debt is the target's 0x54
stack frame and native mesh/delta loop layout; the retained candidate uses a
0x30 frame.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 8.77% (173/671
candidate/target instructions) to 22.85% (563/671), with masked operands
improving from 9 ok, 0 unresolved, 7 mismatch to 28 ok, 0 unresolved, 1
mismatch.

2026-07-03 seed-X reload: spelling the straight seed helper's secondary X as a
reload from the already-written primary center field moves focused Wibo to
23.36% (562/671), with masked operands improving to 29 ok, 0 unresolved, 1
mismatch.

Rejected: moving the curved sample Y/cosine write before the X/sine write raised
focused Wibo only to 23.52% (562/671) while worsening the masked audit from
29 ok, 0 unresolved, 1 mismatch to 28 ok, 0 unresolved, 2 mismatch. The retained
order keeps X before Y until the sine/cosine pairing is better understood.

2026-07-03 retained mesh-face loop: replacing the direct `a`/`b` face writes
with the two-iteration `face_index` loop moves focused Wibo from 23.36% (562/671)
to 26.85% (573/671). Masked operands improve from 29 ok, 0 unresolved,
1 mismatch to 31 ok, 0 unresolved, 1 mismatch; the remaining mismatch is still
the sine/cosine pairing in the curved interior.

Rejected: materializing the curved `sine(angle)`, `cosine(angle)`, and
`sine(half)` calls cleared the masked audit but regressed focused Wibo. The
straight local order fell to 24.88% (567/671) and kept one mismatch; the
interleaved `sine(angle)`, `cosine(angle)`, `sine(half)` order fell to 24.54%
(568/671), with masked operands moving to 30 ok, 0 unresolved, 0 mismatch. Keep
the inline expression until a schedule preserves the fuzzy score.

2026-07-13 terminal ownership: fully expanding `compute_terminal_deltas` into
the method regressed focused Wibo from 26.85% (573/671) to 24.03% (586/671)
and worsened the masked audit from 31 ok, 0 unresolved, 1 mismatch to 25 ok,
0 unresolved, 2 mismatch, so `turnover` retains its local delta-loop sample
pointers. Narrowing the change to direct terminal stores through
`path->primary_samples[path->segment_count - 1]` and the secondary array moves
focused Wibo to 27.80% (581/671), with the masked audit unchanged at 31 ok,
0 unresolved, 1 mismatch. The recovered boundary is terminal-array ownership,
not wholesale helper removal.

2026-07-15 sample ownership cascade: replacing the helper-shaped six-sample
lead-in and two-sample lead-out with direct primary/secondary array ownership,
separate logical Z counters, and the target's do-loop bounds moves focused Wibo
from 27.80% (581/671) to 37.93% (605/671). Retaining the floating curve count,
reusing the incoming `length` slot for the derived radius, and loading the curve
interpolation endpoints from the already-written sample fields also removes the
last masked mismatch.

2026-07-15 curved-body ownership: using separate curve and sample indices,
direct primary/secondary sample fields, the target's sine/cosine call schedule,
inline forward normalization and right-vector cross, and transform-only
secondary propagation moves focused Wibo to 52.22% (612/671). All 36 masked
operands resolve cleanly. The face loop now clears `header_word`, matching the
target's 16-bit store; this is score-neutral but recovers the actual field
width.

Rejected: fully expanding `compute_terminal_deltas` after the curved-body
recovery regressed focused Wibo to 43.26% (619/671), despite clean operands.
Retain the helper boundary until its loop owners can be recovered together.

Rejected: duplicating the parity-specific texture branches around the common
mesh body regressed focused Wibo to 45.83% (625/671). A full Loopbow-shaped
vertex/face mesh transplant fell to 32.79% (689/671) and used a 0x50 frame.
Both encode target-like concepts but not this constructor's source shape.

Rejected: explicitly splitting the terminal and nonterminal mesh vertex paths
with `Vector3` temporaries recovered the exact 0x54 target frame and a
15-instruction prefix, but regressed focused Wibo to 48.64% (657/671).
Combining that shape with duplicated parity branches fell to 45.09% (673/671).
Scalar staging fell to 49.23% (629/671) and lost the recovered frame. Hoisting
the terminal endpoint and passing it through an inlined helper scored 48.98%
(656/671), again with the exact frame and 15-instruction prefix. These probes
locate the remaining frame pressure in the mesh owner without justifying a
lower-agreement rewrite.

## 2026-07-17 live constructor ABI closure

The restarted Binary Ninja session confirms the native `retn 0x18` contract:
`Path* self`, `float length`, integer width and side-exit mode, two surface
textures, and the Windows-only cap texture. This agrees with the portable iOS
`cRPath::BuildTurnover(float, int, bool, char*, char*)` prefix. The stale
database prototype stopped after two textures and mislabeled the final known
stack slot, leaving the cap texture absent.

Guarded recreation and post-write readback now report the exact seven-parameter
prototype with no pending operation. The refreshed caller passes all six stack
operands through `path_pairs[0x25].primary`, and the callee exposes `Path`
fields plus void finalizer flow. This is analysis-only: focused matching remains
52.22% (612/671) with 36 clean masked operands.

## 2026-07-20 live lifetime ownership

A guarded transaction proves nine complete live owners: the primary seed and
mesh samples, primary up vector, secondary position, both terminal deltas, mesh
vertex, and the two face records. Their fields now render directly through
`PathTemplateSample`, `Vec3`, and `ObjectFaceQuad`, with no `__offset`
expressions. A tenth candidate, the pre-biased curved-sample cursor, was
rejected because typing it created two backward `__offset` accesses. Focused
matching remains 52.22% (612/671) with 36 clean masked operands.

## 2026-07-26 mesh-vector ownership

Raw native assembly at `0x4272f9..0x4273c7` proves more source ownership than
the earlier generic terminal/nonterminal probe captured. Both branches own a
separate lateral-offset vector before constructing their generated position.
The terminal branch addresses the previous sample through the current row
cursor and separately owns an endpoint vector whose Z lane is extended by
`1.0f`.

Recovering all four aggregates together supersedes the earlier rejected split.
Focused matching changes from 52.22% (612/671) to 51.89% (651/671), while the
masked audit improves from 36 to 39 clean operands with no unresolved or
mismatched masks. More importantly, the candidate now has the exact native
`0x54` frame and a 15-instruction exact prefix; the previous scalar writer used
a `0x30` frame and had no exact prefix. The small fuzzy regression is retained
because the native aggregate owners, row-cursor relationship, frame, and
prefix all agree.

The adjacent face records remain deferred. Replaying their distinct native
lifetimes before the remaining earlier cursor debt is resolved destabilizes
both Turnover and the already-aggregated Turnunder tail, so the source keeps
the current face loop boundary rather than treating a lower fuzzy result as a
complete ownership recovery.

## 2026-07-27 paired mobile boolean ownership

Exact Android and iOS symbols agree on
`cRPath::BuildTurnover(float, int, bool, char*, char*)`, proving
`bool side_exit` rather than an integer mode. Both portable bodies end at
`CalcLengthZ`; Windows keeps its additional cap texture and local mesh builder.
The shared declaration, replay tooling, and live Binary Ninja prototype now
encode that platform split. The scalar refinement is byte-neutral: focused
matching remains 51.89% (651/671), with a 15-instruction prefix and 41 clean
masked operands.

## 2026-07-28 paired-mobile control ownership

The exact Android and iOS bodies independently preserve the six-sample lead,
two-sample tail, curved body beginning at sample 6, separate curve/sample and
delta/sample cursors, count-derived radius, transform-only secondary copy, and
final `CalcLengthZ` traversal. Windows SSA independently proves the corresponding
native stack definitions, including `curve_count`, `curve_count_f`, the
`curve_count + 8` total, logical indices, byte offsets, and the positive
one-turn `angle`. Mobile evidence supplies source shape only; the Windows ABI,
storage, and mesh tail remain authoritative and unchanged.

The guarded replay now persists those conflict-free lifetimes and is
idempotent on a second run. The refreshed Binary Ninja decompile renders the
owners without `__offset` artifacts. IDA 9.4 also replaces the stale tracked
five-argument `PathTemplate*`/`int32_t` export with the recovered seven-argument
`Path*`/`void` Windows signature and current object/mesh types. This
analysis-only recovery leaves focused matching at 51.89% (651/671), with a
15-instruction prefix and 41 clean masked operands.

## 2026-07-30 terminal-delta array-owner bound

The exact terminal-delta helper shape shared with Twister permits the same
exhaustive direct-array, scoped-pointer, and scoped-reference owner sweep. Both
scoped forms are byte-identical to the retained source. Direct arrays lose
218.23 weighted bytes and fall from 51.89% to **42.92%**, while moving the
candidate from 651 to 657 instructions; the 15-instruction prefix and all 41
references remain clean. Turnover therefore retains its loop-wide pointer
owners.

## 2026-07-30 terminal-delta expression bound

Preserving pointer ownership does not make the authored-operator transfer
viable here. Secondary-only `Vector3::operator-` loses 4.63 weighted bytes,
primary-only loses 19.34, and the paired form loses 23.96. Combining either or
both operators with direct arrays loses at least 218.23 bytes. The retained
51.89%, 651/671-instruction source therefore keeps both component constructors.

## 2026-07-30 authored orientation subtraction

The shared orientation helper's operator form is byte-identical, but the
inline primary expression adds 3.68 weighted bytes. The retained narrow edit
raises focused matching from 51.89% to **52.04%** without changing 651/671
instructions, prefix 15/671, or the 41 clean references. Combining the neutral
helper edit with it emits the same bytes, so only the contributing inline
owner is retained.

## 2026-07-30 mesh arithmetic ownership

Native instructions at `0x4272df..0x4273c7` keep the lateral value on the x87
stack across both terminal and nonterminal branches, construct one lateral
offset per branch, and then add that aggregate to the branch position.
Recovering `double lateral`, both `Vector3::operator*` expressions, and both
`Vector3::operator+` expressions raises focused matching from 52.04%
(651/671) to **53.87%** (647/671), a gain of 44.45 weighted bytes. The
15-instruction prefix and all 41 masked references remain clean.

The scalar owner contributes 0.96 weighted bytes. Either scale operator alone
contributes 7.37, but that unsupported branch asymmetry is rejected; the
evidence-consistent pair still contributes 0.96. The paired position additions
then contribute 42.54. Although the final candidate is four instructions
shorter, every retained change agrees with the native aggregate lifetimes and
improves the weighted match.

Moving the shared vertex owner into either branch loses 15.01 weighted bytes
in all pointer, reference, and direct-index spellings, so the late native
address calculation is treated as compiler scheduling rather than a distinct
source lifetime.

The native face tail still proves separate branch-local records, complete UV
writes, and parity branches at `0x42747a..0x42762c`. Replaying the split records
without parity loses 355.74 weighted bytes and the exact prefix; including the
native parity shape loses 456.83. Those face owners remain deferred until the
earlier loop/cursor lifetimes no longer destabilize the whole function.

## 2026-07-30 fixed-tail index ownership

Windows SSA and both verified mobile bodies expose one logical tail sample
index plus its compiler-derived `0xa8` byte offset. The scratch instead carried
a redundant Z counter alongside the sample index. An exhaustive 11-variant
owner/control sweep shows that sourcing Z from the sample index and testing its
relative two-sample bound together add 35.90 weighted bytes. Removing the now
dead redundant counter is byte-identical to that winner.

The retained source raises focused matching from **53.87%** (647/671) to
**55.34%** (648/671) and, more importantly, extends the exact prefix from
15 to **54/671** instructions. All 41 masked references remain clean. A direct
`segment_count` endpoint reaches the same prefix but gains only 24.18 weighted
bytes in this compilation context.

The corresponding seven-variant lead-index sweep is bounded. A complete
single-index lead is byte-identical, while changing only its control owner
loses 190.08 weighted bytes and collapses the prefix to six instructions. The
neutral lead spelling is not retained.

## 2026-07-30 curved secondary-offset ownership

Native instructions at `0x42709f..0x4270e7` multiply all three primary
`basis_up` lanes by `0.49000001f` before updating the copied secondary
position, and preserve a distinct `secondary_position` owner across those
updates. The prior scalar source instead multiplied and applied each lane
immediately.

Recovering both the authored `Vector3 secondary_offset` value and the
destination pointer raises focused matching from **55.34%** (648/671) to
**56.45%** (647/671), a gain of 26.87 weighted bytes. The exact prefix remains
54/671 and all 41 references remain clean.

The complete three-variant owner sweep confirms the dependency: retaining only
the aggregate loses 15.20 weighted bytes from the winner, retaining only the
position pointer loses 33.87, and restoring the scalar-direct form loses
26.87. The paired source is retained because both native lifetimes and the
bounded compiler result agree.

## 2026-07-30 fixed-sample byte ownership bound

Windows `0x426d1b..0x426de7` preserves a logical lead Z index beside the
`0xa8` sample-byte cursor, and `0x426ded..0x426ee4` preserves a logical tail
index beside its separately derived byte cursor. Replaying both address owners
closes the remaining fixed-sample hypothesis.

The tail byte cursor is exactly byte-identical to the retained indexed source:
**56.45%**, 647/671 instructions, prefix 54/671, with all 41 references clean.
The lead cursor alone loses 57.38 weighted bytes, grows the candidate by two
instructions, and cuts the exact prefix to 15. Adding the neutral tail owner
recovers 20.46 of those bytes and the two instructions, but the pair still
loses 36.92 weighted bytes and keeps the shorter prefix.

The native byte cursors are therefore compiler-derived from the retained
logical owners in this allocation context; no neutral or regressive source
change is kept.

## 2026-07-30 curved-sample byte ownership

The curved loop is the exception to the fixed-sample bound. Windows loads its
current-sample byte offset as `0x3f0` and advances it by `0xa8` at
`0x4270c8`, while the logical curve index remains a separate stack owner.
Addressing both current arrays and the prior primary sample through that
cursor raises focused matching from **56.45%** to **59.77%**, a gain of
80.84 weighted bytes. The candidate moves from 647 to 644 instructions,
retains prefix 54/671, and keeps all 41 references clean.

All 24 nearby cursor initialization and advance-order variants are
byte-identical. Rechecking the fixed owners on the new baseline leaves the
tail cursor byte-identical, while the lead cursor loses 94.58 weighted bytes;
the paired fixed-cursor form still loses 37.00. Only the independently
contributing curved address owner is retained.
