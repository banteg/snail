# initialize_zero_parcel_bucket_pool_thunk

CRT table entry `0x4a105c` points to this one-instruction thunk at `0x4438a0`,
which tail-jumps over 11 alignment nops to the already recovered zero-parcel
bucket constructor. The source-level tail call matches the native 1/1
instruction exactly, with its single masked target resolved.

The direct CRT edge carries the constructor's exact iOS global provenance:
`gGroup0` belongs to `SubGame.o`, so this one-hop startup thunk does too.
