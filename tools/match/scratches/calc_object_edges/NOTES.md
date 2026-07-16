# calc_object_edges

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

Focused Wibo result: 75.62%, 142 candidate instructions versus 141 target
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
