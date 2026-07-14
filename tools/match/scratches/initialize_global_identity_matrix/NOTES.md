# initialize_global_identity_matrix @ 0x44c880

Exact match: 100.00%, 4/4 instructions.

VC6 local `_$E1` initializer for the authored
`TransformMatrix g_identity_matrix(1.0f)` global. The source-level global
definition emits the exact four-instruction body and calls the recovered
single-float matrix constructor directly; no synthetic pointer-returning
wrapper API is required.
