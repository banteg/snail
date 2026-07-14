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
