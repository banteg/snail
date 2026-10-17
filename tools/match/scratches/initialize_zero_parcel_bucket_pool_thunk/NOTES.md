# initialize_zero_parcel_bucket_pool_thunk

CRT table entry `0x4a105c` points to this one-instruction thunk at `0x4438a0`,
which tail-jumps over 11 alignment nops to the already recovered zero-parcel
bucket constructor. The source-level tail call matches the native 1/1
instruction exactly, with its single masked target resolved.

The direct CRT edge carries the constructor's exact iOS global provenance:
`gGroup0` belongs to `SubGame.o`, so this one-hop startup thunk does too.

## 2026-10-17 compiler-generated pair

The thunk and body are VC6's dynamic-initializer pair for the global definition
`ParcelBucket g_zero_parcel_buckets[PARCEL_BUCKET_CAPACITY]`, which replaces
the hand-written wrapper and initializer function. Both scratches compile the
one source file, the body as `_$E4` and the thunk as `_$E5` in the whole
SubGame TU (VC6 numbers each initialized declaration's pair in steps of three).
Here `ParcelCandidate` now declares the folded no-op constructor at `0x408600`,
so `ParcelBucket`'s implicit constructor builds its candidate array through
VC6's vector constructor iterator `??_H`, the image's first function at
`0x401000`. Both functions stay exact, with every masked operand resolved
through the `function_alias` reference entries.
