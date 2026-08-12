# add_object_edge

Current recovery: semantic-complete (`compiler,references` residual). Exact
Android/iOS `cRObject::AddEdge` bodies establish the common reverse-edge merge
algorithm; Windows proves its larger record, normalized direction/length, and
static coplanar-join filter. No reference is unresolved or mismatched. Three
known global edge-count operations remain unaudited because the native and
candidate publish the same decrement through different block layouts.

First source-shaped scratch for the toon edge merge helper.

Semantics:

- skips edges whose source facequad normal is shorter than about `0.9`;
- searches the temporary edge array for the same geometric edge in reverse,
  comparing vertex positions rather than only vertex indices;
- creates `OBJECT_TOON_EDGE_FLAG_BOUNDARY` edges with vertex indices, normal A, a
  normalized edge direction, and its original length;
- when the reverse edge is found, replaces that bit with
  `OBJECT_TOON_EDGE_FLAG_SHARED`, records normal B, and optionally removes
  internal joins when the normal cross product is near-flat or points with the
  stored edge direction.

This scratch uses the shared `ObjectToonEdge` layout and the temporary globals
also consumed by `calc_object_edges`.

Focused Wibo result: 39.72%, 201/227 candidate/target instructions, with 11
clean masked operands and one masked mismatch. The main remaining gap is block
layout: native places the add-new-edge path before the found-edge merge/removal
path, while this natural search/add-or-merge spelling still emits the add-new
tail after the merge path.

2026-06-20 branch-layout improvement: rewriting the post-search branch as
`if (found_edge == 0) { add new edge; return; }` moves the add-new-edge path
ahead of the merge/removal path in source and raises focused Wibo to 43.93%
with 201/227 candidate/target instructions and 12 clean masked operands. The
remaining gap is still broad register/frame ownership in the search and merge
blocks, plus the existing shifted global-count/global-edge masked comparison.

2026-07-10 ownership recovery: native dword loads and stores show that
`ObjectToonEdge::vertex_a` and `vertex_b` are full 32-bit indices at `+0x04`
and `+0x08`, not padded 16-bit fields. The search walks the `vertex_b` dword
lane of the global scratch array, while add and merge paths repeatedly address
`g_object_edge_build_edges[index]` rather than retaining a record pointer.
The add path also normalizes its local direction first, stores the returned
original length, and only then copies the normalized vector into the edge.
Those source-shape and ownership corrections raise focused Wibo to 61.95%,
with 225/227 candidate/target instructions and 28 clean masked operands.

Index-only search results, scalar/vector temporary splits, cached merge-record
pointers, and a structured `goto` were tested and rejected because they
regressed the native block, frame, or register shape. The remaining gap is
primarily local/register allocation and temporary lifetime rather than a known
ownership ambiguity.

2026-07-12 vector lifetime and dot-contract pass: native reserves a distinct
function-lifetime `direction` value instead of reusing its lane for the
merge-only right-hand normal. Keeping that normalized direction separate from
the raw `end - start` delta recovers the native `0x38` stack frame and makes the
record contract explicit: `length` owns the pre-normalization magnitude, while
`direction` owns the normalized vector copied into the edge.

The merge path also confirms that member `Vector3::dot_vector` returns a
`float` source value. Native compares ST0 directly with the 32-bit
`0.0020000001f` constant; the old shared `double` declaration forced a qword
constant at this callsite. Correcting the shared return type keeps the exact
dot helper and toon renderer exact and raises this scratch to 73.36%, 231/227
instructions, prefix 1/227, with 29 clean operands and no unresolved or
mismatched operands.

The found-edge state is only a search sentinel; indexed-only search state
regressed to 72.05%, and a direct native-shaped merge `goto` moved the merge
block ahead of the add path and regressed to 57.02%. The honest residual is
register/block allocation, not an unresolved edge-record owner or field.

The iOS ARMv6 symbol `cRObject::AddEdge(int, int, int)` and all six Windows
calls from `calc_object_edges` prove the receiver and three integer formals.
No caller consumes a result. BN's old fourth `float*` argument was a stack
recovery error, not a hidden vector input; the shared analysis slice now uses
the source-shaped void Object method while leaving the 73.36% block-layout
residual visible.

The merge-path dot operand now uses the recovered const-reference member
surface directly. VC6 emits the same 231/227 candidate/target instructions,
73.36% score, and 29 clean operands, so the ownership clarification introduces
no new matching scaffolding.

## 2026-07-15 shared workspace replay

The two temporary globals are now named and typed in the repeatable Binary
Ninja slice as `g_object_edge_build_edges: ObjectToonEdge*` and
`g_object_edge_build_count: int32_t`. The refreshed artifact keeps the Object
receiver and those borrowed globals visible; the honest 73.36% block-layout
residual is unchanged.

## 2026-07-16 dynamic-topology policy

The internal-join cull now consumes `OBJECT_FLAG_DYNAMIC_VERTICES` instead of
an isolated `4`. Startup and logo initialization produce that bit on animated
objects, while grouped-buffer construction and vertex-buffer refresh consume
it to retain source-vertex ownership across updates. This edge builder is the
topology-side consumer: static objects may discard flat shared joins, but
objects whose vertices move retain them so later normal changes cannot expose
a missing toon edge. The focused result remains byte-identical at the honest
73.36%; no new flag meaning was inferred.

## 2026-07-18 typed edge-bank replay

The IDA replay now gives `g_object_edge_build_edges` its proven
`ObjectToonEdge*` type, verifies the record's exact 0x24-byte extent, and keeps
the search, found, shift, and copy indices as distinct saved locals. The
refreshed decompile consequently renders boundary/shared flags, both vertex
indices, both normal indices, direction, length, and record copies through
typed fields. Address-anchored BN and IDA names make that ownership repeatable
even when a database begins with an autogenerated function symbol.

Focused Wibo remains 73.36%, 231/227 instructions, prefix 1/227, and 29 clean
masked operands. No source-shape probe was retained because the remaining
four-instruction/block-allocation delta contains no newly unresolved owner.

## 2026-07-23 edge merge lifetime replay

The guarded BN replay now separates the native reuse of the incoming
`vertex_b` stack slot at `0x4305f8`: the function ABI remains an `int32_t`, while
the post-store lifetime is a borrowed `Vec3*` used during reverse-edge search.
Optimized HLIL propagates that borrow into a typed `eax_3` expression rather
than preserving the user name, but no longer lets the pointer type escape back
into the formal.

The same replay records each complete vertex borrow, both face-normal borrows,
the normalized output direction, and both whole-record operands of the
0x24-byte edge shift. It deliberately leaves the EBP search value as an
`int32_t*` cursor into each edge's `vertex_b` field and leaves the two scaled
ESI/EAX values as byte offsets; neither interior address owns an
`ObjectToonEdge`. The refreshed artifact consequently exposes the vector
members and record copy without inventing wider owners.

BN's PartialAccessAnalysis still renders the first normal's `x` and `y` dword
loads as byte-lane assignments. That is a decompiler presentation residual,
not four native byte loads. Focused Wibo remains 73.36%, 231/227 instructions,
prefix 1/227, and 29 clean operands; the remaining delta is still honest
register/block allocation.

## 2026-07-27 dual-mobile algorithm confirmation

The Android and iOS bodies retain the exact void
`cRObject::AddEdge(int, int, int)` owner. Across all three ports the method
rejects a source normal below `0.9`, compares endpoint positions rather than
trusting vertex indices, searches for the reverse orientation, creates a
boundary record when none exists, and converts the first boundary match into a
shared edge with a second face-normal index.

The record layout intentionally diverges. Both mobile ports store a compact
five-halfword, ten-byte edge and stop after the boundary/shared merge. Windows
owns the richer 0x24-byte `ObjectToonEdge`: 32-bit indices, normalized edge
direction, original length, and the static-object cross/dot tests which remove
flat or inward joins. Mobile proves the owner and common algorithmic prefix;
it does not justify shrinking the Windows record or deleting its desktop-only
filtering.

## 2026-07-29 boolean search state and cursor order

Seven recorded sweeps and two complete-source probes cover 43 unique variants
around the remaining parameter, search, add/merge, vector, and removal-tail
lifetimes. Two source recoveries materially improve the Windows candidate.

First, the former `ObjectToonEdge* found_edge` never supplied an edge owner:
the merge path indexes the global bank with the loop counter and consumes only
whether the reverse edge was found. Replacing that unused record pointer with
a `bool` raises focused matching from 73.36% to 81.68%, advances the exact
prefix from 1 to 15 instructions, and reduces candidate-only reference debt.
Integer and boolean sentinels compile identically; the boolean is retained
because Android and iOS both express the match as a control-flow fact and
return directly from it.

Second, all three binaries materialize `vertices[vertex_b]` before borrowing
the global edge cursor. Reversing those two typed declarations raises the
candidate again to **86.53%**, target/candidate `227/226`, prefix `15/227`,
with 33 clean operands and five explicitly unaudited block-layout operands.
Split assignment and a cached `vertices` owner compile identically, so the
shortest position-before-cursor spelling is retained.

The surrounding owner hypotheses are now bounded. Named normal-index and
receiver owners are byte-neutral, as are all nine search-local declaration
orders. Add/merge `else if` and guarded fallthrough forms do not alter
epilogue placement. Narrow object/edge-bank owners remain neutral, while
preloading flags regresses. Five ordinary whole-vector declaration forms are
neutral and pointer/index owners regress to 74.61%–80.35%. Six read/modify/
publish spellings for the final global count all canonicalize to the same
in-memory decrement.

The recorded sweeps document the residual. The remaining Windows-only filter
differs in saved-register allocation, early epilogue
restoration on the new-edge path, and the final count-decrement schedule. No
mobile layout or compact-record behavior is imported, and no register hint,
volatile barrier, dummy dependency, or synthetic owner is used to force those
choices.
