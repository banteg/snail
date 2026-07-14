# initialize_global_identity_matrix_thunk @ 0x44c870

CRT constructor-table entry at `0x4a1068`. A source-level definition of
`g_identity_matrix(1.0f)` makes VC6 emit the exact local `_$E2` thunk, which
tail-forwards to the adjacent `_$E1` initializer. This recovers both functions
as compiler products of one authored global instead of hand-written wrappers.
