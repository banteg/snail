# initialize_supertramp_path_template_pair

Ownership reconstruction for
`initialize_supertramp_path_template_pair @ 0x423f10`.

The native tail is `ret 0x1c`, matching seven explicit stack arguments. This
constructor allocates an extra sample before decrementing `segment_count`, then
uses the final allocated sample directly in the mesh. The scratch models the
flat approach, circular supertramp arc, separate secondary radius, direct mesh
rows, deltas, and finalization.

The retained scratch now matches 68.00% (545/552 candidate/target
instructions), with a 16-instruction exact prefix, an exact 0x2c stack frame,
and masked operands at 36 ok, 0 unresolved, 0 mismatch, 0 unaudited. Residuals
are primarily register allocation, stack-home selection, and store scheduling;
this is not an exact match.

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

2026-07-20 live mesh-owner closure: transactional MLIL preview recovers a
complete primary lead-in sample, both curved-section right vectors, the
secondary curved sample, the primary mesh sample, each complete generated
`Vec3` vertex, and both complete facequad records. These eight lifetimes expose
direct sample, transform, vertex, texture, and UV fields without introducing
an `__offset` expression. The replay extends ownership from the path arrays
into the object mesh while preserving the independently proven constructor
shape. This is analysis-only: focused Wibo remains 51.62% (529/552), with a
15-instruction prefix and 32 clean masked operands.

2026-07-26 face-owner completion: the native front face at
`0x4244eb..0x424584` and back face at `0x4245b0..0x42464a` each own their
complete record, including the header, indices, texture lookup, and all four
UV pairs. Moving the face pointer and final `uv[3].v` write into each branch
recovers that ownership boundary and raises focused Wibo from 51.62% to
54.53% (529 to 541 candidate instructions), with the exact prefix growing
from 15 to 17 and all 32 audited operands still clean.

This is a coupled lifetime result: duplicating only the native final UV write
reaches 52.09%, while moving the already complete mesh vertex destination
below its generated-position temporary is byte-neutral. The adjacent `start`
constructor independently confirms the duplicated UV completion but rejects
branch-local face pointers, so the retained Supertramp owner shape is not a
blind family transfer.

## 2026-07-27 mobile-authored selector type

Android and iOS both expose
`cRPath::BuildSuperTramp(float, float, int, bool, char*, char*, char*)`.
Their bodies identify the portable leading float as a lateral center offset,
followed by length and width. Windows omits that leading offset, retains the
logical Boolean side selector after width, and owns one additional unused
texture slot before the terminal cap texture. This reconciles the platform
ABIs without forcing the mobile argument list onto Windows.

Promoting Windows `side_exit` from `int32_t` to `bool` is byte-identical:
focused matching remains 54.53% (541/552 candidate/target instructions), with
a 17-instruction exact prefix and 36 clean masked operands. The seven Windows
stack arguments and all four texture owners remain unchanged.

## 2026-07-28 paired-mobile control ownership

Android and iOS independently retain SuperTramp's portable control graph: a
seven-sample flat lead, a post-tested circular arc, and a fresh delta pass.
They agree on the derived curve count, primary and secondary radii, curve
phase, and separate sample index/cursor pairs. They are source-shape evidence
only: the mobile ABI includes a leading lateral-center float and has a
different texture split, while this Windows build's seven stack arguments,
sample counts, constants, and `0xa8`-byte sample layout remain authoritative.

Exact Windows MLIL definitions now recover `curve_count` across its EAX/spill
lifetime, split the overwritten length home into `curve_radius`, and expose
`lead_sample_index`/`lead_sample_offset`, `curve_index`/
`curve_sample_offset`, `secondary_radius`, `curve_phase`, `delta_index`, and
`delta_sample_offset`. This removes the false reuse of `width_cells_`,
`length`, and generic EDI cursors across those three logical passes.

A previewed `curve_count_f` annotation was rejected: the stored float is real,
but current HLIL folds the spill away and never renders the owner. Keeping it
would add replay state without improving the recovered source. The retained
partition was previewed transactionally and rolled back cleanly before live
application.

The live transaction saved successfully and a second replay reported every
control owner already current. Strict focused Binary Ninja and IDA 9.4 exports
report zero mismatches, and all 1,142 decompile health checks pass. The IDA
refresh also closes its stale artifact onto the independently proved Windows
`Path*`, Boolean selector, and four-texture ABI.

Matcher source and bytes are unchanged: focused matching remains **54.53%** at
**541/552** candidate/target instructions, prefix **17/552**, with **36
accepted, 0 unresolved, 0 mismatched, and 0 unaudited** masked operands.

## 2026-07-30 authored terminal-delta subtraction

The exact shared terminal-delta block supports the paired authored
`Vector3::operator-` form. The exhaustive two-site sweep adds 7.08 weighted
bytes and raises focused matching from 54.53% to **54.89%**. Candidate and
target counts remain 541/552, prefix remains 17/552, and all 36 references stay
clean; either isolated operator gains half as much.

## 2026-07-30 generated-position operator boundary

Raw native `0x4243a2..0x424418` keeps the lateral value live on x87 while it
materializes a lateral-offset vector and then one complete generated position.
Spelling the final sum through the authored `Vector3::operator+` adds 3.54
weighted bytes and raises focused matching to **55.08%**. Candidate and target
counts remain 541/552, prefix remains 17/552, and all 36 references stay clean.
The scale operator alone is byte-neutral.

Three following bounded sweeps close the adjacent ownership choices:

- changing the lateral local to `double` loses 14.16 weighted bytes; pairing
  it with `Vector3::operator*` is byte-neutral but does not beat the retained
  float/component form;
- moving the shared loop-index declaration across five setup boundaries is
  byte-neutral;
- initializing that index early enough to overlap the count/radius setup loses
  3.54 to 14.16 weighted bytes and can shorten the exact prefix.

The first residual remains the native `0x40` versus candidate `0x44`
count/radius stack-home swap. The semantic lifetime probes do not reproduce
it, so no allocator forcing is retained.

## 2026-07-30 post-cascade arc byte cursor rejected

The explicit arc cursor was retested after the direct initializer,
orientation, delta, and generated-position ownership cascade. Windows loads
the seven-sample byte offset `0x498` into `edi` at `0x424099`, increments the
logical arc index separately at `0x424257`, advances the cursor by `0xa8` at
`0x424258`, and tests the logical index at `0x42425e`.

Replaying that physical address owner across both arc arrays falls from
**55.08%** to **54.89%**. Candidate and target counts remain 541/552,
prefix remains 17/552, and all 36 references stay clean; the cursor loses
exactly 3.54 weighted bytes, equal to the independently proven
generated-position `Vector3::operator+` gain.

Placing the cursor before or after the secondary radius and logical-index
initialization, and removing the now-dead derived sample index, all compile
byte-identically. The reverse probe is recorded and the 55.08% source is
restored. Supertramp therefore keeps direct array ownership: the native arc
byte cursor remains compiler-derived, and it is not used to trade away a
separate authored operator boundary.

## 2026-07-30 lead, count, and mesh-grid ownership

Three native-backed owner boundaries materially improve the post-cascade
scratch:

- The Windows lead loop advances a physical `0xa8`-byte sample cursor and tests
  that cursor against the seven-sample `0x498` span. Recovering the explicit
  offset raises focused matching from 55.08% to **56.91%**, adding 35.41
  weighted bytes with candidate/target counts unchanged at 541/552, prefix
  unchanged at 17/552, and all 36 references clean. Testing the logical index
  instead reaches only 55.41% and falls three instructions farther from the
  target.
- Deriving the allocated count directly as `curve_segments + 8`, then deriving
  `segment_count_f` from the stored member predecessor, raises focused matching
  from 56.91% to **62.72%** and adds 112.40 weighted bytes. Candidate size
  closes from 541 to 545 instructions; the exact prefix trades from 17 to 16
  because the first count spelling moves three bytes earlier. A named
  predecessor local is byte-identical, while storing the float before the
  member returns exactly to 56.91%.
- Windows MLIL keeps the vertex grid and face grid in separate row/column
  owners. Giving the face phase fresh `face_row` and `face_column` lifetimes
  raises focused matching from 62.72% to **68.00%**, adding 102.31 weighted
  bytes with counts fixed at 545/552, prefix fixed at 16/552, and all 36
  references clean. The recorded reverse sweep aliases those owners back to
  the vertex grid and reproduces the complete 62.72% regression.

The native vertex sample offset begins only after the empty-grid guard, the
face column advances as one owner, and the flat and curved sample indices are
logically distinct. Recovering those source boundaries is byte-neutral in the
retained context but removes false cross-phase ownership. Declaring the curve
radius before its floating count is also byte-neutral and is rejected in favor
of the simpler initialized declaration.

The remaining broad mesh residual is an allocator frontier: Windows spills the
vertex row and keeps the physical sample offset in a register, while the
candidate keeps the row in a register and spills the offset. Ordinary
declaration-order and lifetime changes do not reproduce that swap, so no
padding, volatility, artificial register binding, or other allocator forcing
is retained.

## 2026-07-30 post-grid arc cursor replay

The native arc byte cursor was replayed once more after the lead, count, and
face-grid ownership gains raised the retained baseline to **68.00%**. In this
context, spelling the separate `0x498`/`0xa8` physical cursor across both arc
arrays is decisively worse: focused matching falls to **61.48%**, losing
126.19 weighted bytes and four candidate instructions.

The exact prefix remains 16/552 and all 36 references remain clean, so the
regression is code ownership rather than a masking artifact. The recorded
reverse probe restores the full **68.00%**, **545/552** retained receipt.
Direct indexed arc ownership is therefore closed on the stronger post-grid
baseline as well.

## 2026-07-30 post-count lifetime bounds

The count and face-grid recoveries leave two explicit stack-owner swaps in the
68.00% candidate. Native assigns the count/radius predecessor to stack home
`0x40` and the lead logical index to `0x44`; the candidate assigns those
owners in reverse. In the mesh vertex phase, native spills the row owner and
keeps a distinct physical sample-offset lifetime, while the candidate keeps
the row in EBX and spills the offset.

Both hypotheses were replayed only after the count and grid cascade, so the
earlier pre-cascade declaration results were not treated as permanent. Moving
the lead index and offset declarations across the curve count, radius, and
`get_path_nodes` boundaries, reversing their declaration order, and separating
their initialization produces five byte-identical candidates. Initializing
the offset first loses 3.54 weighted bytes.

The vertex grid is equally bounded. Declaring the sample offset before the row
or after the column, initializing it before the row, and initializing the row
at declaration all compile byte-identically. Narrowing the row into the
non-empty guard, in either declaration order, loses 3.54 weighted bytes.
Every variant preserves 545/552 instructions, prefix 16/552, and all 36 clean
references except the scoped-row forms, which retain the same instruction
count and audit while losing the four weighted bytes.

No source edit is retained. These results raise the experiment ledger's
trailing non-improvement streak to four and formally stall the local lifetime
frontier at **68.00%**. Resolving either stack-home swap now requires a new
semantic owner or source provenance, not declaration shuffling, volatility,
padding, or forced allocation.

## 2026-07-31 direct face-offset record ownership

The local-lifetime stall above did not cover direct indexed record writes.
Hoisting the semantic face offset before the front/back selection and
addressing every field as `facequads[face_offset]` raises focused matching from
**68.00%** to **77.37%**. Candidate size moves from 545 to 544 instructions
against the 552-instruction target, while the exact 0x2c frame, 16/552 prefix,
and all 36 clean references are preserved.

Four algebraically equivalent offset spellings are byte-identical. Cage2,
Worm, and Turnover independently reject the same transfer, so this is retained
as Supertramp's source boundary rather than a universal mesh rewrite.

## 2026-07-31 acquisition-order score artifact

Swapping the mesh banks raises aggregate matching from **77.37%** to
**77.92%**, adding 10.59 weighted bytes without changing size, prefix, or
references. Native nevertheless loads vertices at `0x424370` before
facequads at `0x424377`, exactly matching the retained source. The contrary
score-only order is recorded and rejected rather than replacing a proven
instruction sequence.

## 2026-07-31 post-face arithmetic replay

The lateral and scale grids were replayed after direct face ownership. Member
scaling remains byte-neutral, as does its interaction with a double lateral
owner. Double lateral alone loses 14 weighted bytes; split float is neutral;
the other double and volatile forms lose 18–35 weighted bytes, with one
double-expression form also adding two unaudited references.

No variant exceeds the retained **77.37%**, 544/552 instructions, prefix
16/552, with 36 clean references. The pre-face arithmetic boundary therefore
survives the new allocation unchanged.
