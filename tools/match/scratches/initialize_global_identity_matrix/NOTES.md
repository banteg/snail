# initialize_global_identity_matrix @ 0x44c880

Exact match: 100.00%, 4/4 instructions.

VC6 local `_$E1` initializer for the authored
`TransformMatrix g_identity_matrix(1.0f)` global. The source-level global
definition emits the exact four-instruction body and calls the recovered
single-float matrix constructor directly; no synthetic pointer-returning
wrapper API is required.

## 2026-08-12 source-unit provenance

The symbol-preserving iOS inventory assigns the exact identity-transform
global `gUnitMatrix` to `RMaths.o`. Windows has one 0x40-byte matrix global,
and this sole xref constructs it with the scalar `1.0f` form that emits the
identity matrix. This recovers the initializer's source unit without claiming
a mobile function map.
