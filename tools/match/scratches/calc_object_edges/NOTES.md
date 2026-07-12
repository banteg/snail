# calc_object_edges

First source-shaped scratch for the toon edge builder.

Semantics:

- only runs when object `flags & 1` is set;
- uses the archive-data base as a temporary `ObjectToonEdge` array at
  `data_503300` and tracks the live count at `data_503318`;
- emits three directed edges for the first triangle of every facequad, plus the
  second triangle when the quad is not marked with `0x80`;
- when `flags & 0x8000` is set, removes boundary-only edges before requesting
  and copying the final edge array.

This scratch also promotes the shared `ObjectToonEdge` layout used by
`render_object_toon`, `request_object_edges`, and this builder.

Focused Wibo result: 71.63%, 141/141 instructions, with 10 clean masked
operands and three masked mismatches caused by current setup/removal-region
alignment. The candidate COFF relocations for `g_object_edge_build_edges` and
`g_object_edge_build_count` are source-correct; the mismatch report pairs a
shifted setup store against the wrong native store until the prologue/local
shape is improved.

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
