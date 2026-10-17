# initialize_parcel_set_bucket_pool_thunk

CRT table entry `0x4a1058` points to this one-instruction thunk at `0x443860`,
which tail-jumps over 11 alignment nops to the already recovered parcel-set
bucket constructor. The source-level tail call matches the native 1/1
instruction exactly, with its single masked target resolved.

The direct CRT edge carries the constructor's exact iOS global provenance:
`gGroup` belongs to `SubGame.o`, so this one-hop startup thunk does too.

## 2026-10-17 compiler-generated pair

The thunk and body are VC6's dynamic-initializer pair for the global definition
`ParcelBucket g_parcel_set_buckets[PARCEL_BUCKET_CAPACITY]`, which replaces the
hand-written wrapper and initializer function. Both scratches compile the one
source file, the body as `_$E1` and the thunk as `_$E2` in the whole SubGame TU
(VC6 numbers each initialized declaration's pair in steps of three). Here
`ParcelCandidate` now declares the folded no-op constructor at `0x408600`, so
`ParcelBucket`'s implicit constructor builds its candidate array through VC6's
vector constructor iterator `??_H`, the image's first function at `0x401000`.
Both functions stay exact, with every masked operand resolved through the
`function_alias` reference entries.
