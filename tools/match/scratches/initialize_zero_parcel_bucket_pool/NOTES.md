# Exact match

`initialize_zero_parcel_bucket_pool` @ 0x4438b0 clears the zero-parcel fallback
bucket pool at `data_53d190`.

Its source shape mirrors `initialize_parcel_set_bucket_pool`: `0x800` buckets,
bucket stride `0x20c`, `0x20` slots per bucket, slot stride `0x10`, and the
real shared callback at `0x408600`. That callback is the generic
`noop_runtime_slot_constructor` (`mov eax, ecx; ret`), not a parcel-specific
initializer.

The exact loop source is a pointer cursor plus explicit `0x800` countdown,
matching native's `esi` bucket pointer and `edi` counter.

2026-07-14 extent cleanup: the emitted countdown, candidate stride, and
candidate count now come from `PARCEL_BUCKET_CAPACITY`,
`sizeof(ParcelCandidate)`, and `PARCEL_CANDIDATE_CAPACITY`. The constructor
remains exact at 15/15 instructions with all three operands clean.

## 2026-08-12 source-unit provenance

The symbol-preserving iOS inventory assigns the exact cross-port `gGroup0`
global to `SubGame.o`. Live Windows xrefs restrict this pool to this constructor
and the verified `cRSubGame::PlaceParcels()` body; the constructor is also
physically bracketed by verified `SubGame.o` functions. This recovers its
Windows source object while leaving the absent mobile constructor unmapped.

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
