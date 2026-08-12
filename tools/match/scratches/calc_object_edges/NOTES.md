# calc_object_edges

Current recovery: semantic-complete (`compiler` residual). Exact Android/iOS
`cRObject::CalcEdges` bodies establish the authored build/compact/transfer
lifecycle, while Windows proves its 0x30-byte face topology and 0x24-byte toon
edge records. All 17 references are clean; the one-instruction delta is the
documented one-slot versus two-slot VC6 cleanup-loop allocation.

First source-shaped scratch for the toon edge builder.

Semantics:

- only runs when `OBJECT_FLAG_BUILD_TOON_EDGES` is set;
- uses the archive-data base as a temporary `ObjectToonEdge` array at
  `data_503300` and tracks the live count at `data_503318`;
- emits three directed edges for the first triangle of every facequad, plus the
  second triangle when `OBJECT_FACEQUAD_FLAG_TRIANGLE` is clear;
- when `flags & 0x8000` is set, removes
  `OBJECT_TOON_EDGE_FLAG_BOUNDARY` records before requesting and copying the
  final edge array.

This scratch also promotes the shared `ObjectToonEdge` layout used by
`render_object_toon`, `request_object_edges`, and this builder.

Focused Wibo result: 77.74%, 142 candidate instructions versus 141 target
instructions, with 14 clean masked operands and no unresolved or mismatched
operands. The remaining gap is the cleanup-loop allocation: native reuses one
stack dword across the face and edge phases, while VC6 currently spills both
the edge index and its strength-reduced byte offset into an eight-byte frame.

2026-06-21 removal-loop follow-up: swapping the two setup stores is
codegen-neutral at 71.63% and leaves the same shifted masked-pairing report.
Replacing the byte-offset removal loop with a pointer cursor reduces the masked
mismatch count, but regresses the instruction stream to 56.83% by losing the
native face-loop and local-slot shape; a pointer variant that reuses the reloaded
count drops further to 53.57%. Keep the offset loop until a form preserves the
opening face traversal as well as the cleanup region.

2026-07-12 workspace-owner clarification: the pointer returned by
`get_archive_data_base` and the pointer reloaded after `add_object_edge` calls
are the same borrowed `build_edges` view of the shared workspace. The source
now refreshes that one variable instead of inventing a second
`scratch_edges` owner. This is codegen-neutral at 71.63% and preserves all 141
instructions; the remaining `0x8` candidate frame versus native's one-dword
frame comes from the cleanup loop spilling both index and byte offset. Pointer,
register-hint, and cross-phase-index reuse probes did not recover that native
allocation and were not retained.

The local ARMv6 symbol table retains this method as `cRObject::CalcEdges()` in
`RObject.o`, and the sole Windows build-loop caller discards EAX. The checked-in
analysis headers and BN/IDA sync now correct the old `void __fastcall(char*)`
transcription to a void Object thiscall. This clarifies ownership for the six
`AddEdge` calls without claiming the remaining cleanup-loop frame mismatch is
solved.

2026-07-14 typed cleanup and cross-build pass:

- `edge_count` now begins as the local zero installed in the global workspace
  count. It is refreshed with `build_edges` only after the face loop actually
  calls `add_object_edge`; the zero-face path keeps the original scratch pointer
  and count, matching the native control-flow ownership.
- The face-loop tail advances the borrowed face pointer, face index, and paired
  normal index in native order. This removes the last otherwise-identical tail
  scheduling mismatch.
- The removal loop now addresses `build_edges[index]` and copies typed adjacent
  `ObjectToonEdge` records rather than maintaining source-level byte offsets.
  VC6 independently strength-reduces those indices into the native-style
  running offset. The checked-in Android `cRObject::CalcEdges` implementation
  corroborates the same indexed edge-array compaction and global scratch owner,
  despite that platform's smaller edge representation.
- Together these source/ownership corrections raise the focused result from
  71.63% (141/141, 10 clean and three mismatched operands) to 75.62% (142/141,
  all 14 operands clean). Pointer cursors, explicit register hints, and raw
address spellings remain rejected; the two-spill versus one-spill allocator
residual stays visible rather than being fakematched.

## 2026-07-15 shared workspace replay

The repeatable Binary Ninja slice now types and names the temporary edge bank
and count globals. The refreshed artifact follows `ObjectFaceQuad*` input,
six Object-member edge calls, the shared workspace, and the final retained
`Object::edges` bank without `arg1` or anonymous `data_5033xx` owners. Matching
remains honestly partial at 75.62%.

## 2026-07-18 shared topology workspace replay

Both replay lanes now address-anchor the builder and its edge-merge helper.
IDA additionally types `g_object_edge_build_edges` as `ObjectToonEdge*`, names
the borrowed archive view `build_edges`, and persists the face, normal, edge,
shift, and byte-offset loop owners. Its artifact now follows the complete
handoff from `get_archive_data_base()` through six member calls and typed
0x24-byte compaction into `Object::edges`; paired health checks reject the old
byte-bank transcription.

Focused Wibo is unchanged at 75.62%, 142/141 instructions, prefix 0/141, and
14 clean masked operands. The candidate's extra stack spill remains visible;
no pointer cursor, raw address spelling, or other fakematch was introduced.

## 2026-07-23 builder lifetime replay

Native allocates this function's only local dword with `push ecx`. That
physical slot first preserves the Object receiver, then holds the face index,
and finally holds the edge-compaction byte offset. The guarded BN replay now
separates all three logical lifetimes: the face zero, loop phi, and back edge
merge into `face_index`, while the compactor zero, loop phi, and back edge
merge into `edge_byte_offset_spill`. The retained initial lifetime remains an
Object borrow without contaminating either scalar loop.

EDX and its spill remain integer byte offsets into the temporary edge bank.
Only the addresses formed after adding those offsets to `build_edges` receive
`ObjectToonEdge*` ownership; optimized HLIL folds those short-lived ESI/EDI
borrows directly into the 0x24-byte copy. The final whole-bank transfer keeps
the source and destination banks typed, while the post-`rep movsd` ESI/EDI
values are correctly byte-oriented tail cursors rather than new edge owners.

The replay work also tightened the shared split helper. It may now extend an
existing merge only when the current sources are a subset of the requested
sources for the same target, and it resolves BN-hidden merged sources through
the split and merge maps. Conflicting targets and unexpected sources still
abort before mutation. This makes export-driven lifetime refinements
repeatable instead of requiring an unsafe manual merge replacement.

Focused Wibo remains 75.62%, 142/141 instructions, prefix 0/141, and 14 clean
masked operands. The remaining extra spill and cleanup-loop allocation delta
are unchanged and visible; no matching source or masked operand was altered.

## 2026-07-27 dual-mobile lifecycle confirmation

Android and iOS preserve the exact void `cRObject::CalcEdges()` owner and the
same complete lifetime as Windows: gate on the toon-edge Object flag, borrow
the global scratch edge bank, clear its shared count, call `AddEdge` across the
active face topology, compact boundary records when Object flag `0x8000` is
set, allocate the retained Object-owned bank once, and copy the final scratch
records into it.

The topology and storage are platform projections, not interchangeable
layouts. Mobile walks a GL index array in triples and stores ten-byte compact
edges (plus a mobile edge-index bank); Windows walks 0x30-byte
`ObjectFaceQuad` records, emits three edges for a triangle and six for a quad,
and retains 0x24-byte `ObjectToonEdge` records for the DirectX toon renderer.
Only the method owner and lifecycle transfer.

## 2026-07-29 cleanup schedule sweep

The retained compaction loop now copies `build_edges[shift_index + 1]` into
`build_edges[shift_index]` before incrementing `shift_index`. This is the
source-shaped authored loop: native forms both record addresses first, advances
the scalar shift index, and then executes the nine-dword copy. Publishing the
reduced shared edge count before decrementing the local outer index also gives
VC6 the native store schedule without changing the removal semantics. Together
these two changes improve the focused result from 75.62% to 77.74%, or 297 of
382 fuzzy bytes, while retaining 142 candidate instructions against 141 target
instructions and all 14 audited references clean. The exact prefix remains
zero because the frame-allocation difference begins at the prologue.

Six recorded sweeps cover 106 unique variants: nine improve an earlier
baseline, 52 are byte-identical, and 45 regress, with no compile failures or
repeated source/compiler variants. The tested space includes explicit
working/saved offsets, separate outer/shift offsets, typed and raw flag views,
setup declaration orders, `register` hints, live-zero comparisons, copy and
publication schedules, and structured `do`, `while`, and `for` controls. The
single winning schedule is retained; three trailing non-improving sweeps
document the tested frontier without closing it.

The remaining allocator residual is now narrower rather than hidden. Native
keeps `build_edges` in EDI and the outer edge index in EAX, spilling only the
strength-reduced byte offset into the one reused local dword. The candidate
keeps `build_edges` in EAX and spills both its EBX edge index and EDX byte
offset into an eight-byte frame. Replaying the declaration/register sweep
against the improved source was intentional interaction coverage; all 106
compiled variants are source-unique even though the experiment summary notes
the reused mutation specification.
