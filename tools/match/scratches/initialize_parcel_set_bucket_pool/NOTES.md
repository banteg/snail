# Exact match

`initialize_parcel_set_bucket_pool` @ 0x443870 clears the positive-count
parcel-set bucket pool at `data_6487e8`.

Each of the `0x800` buckets has stride `0x20c`. The initializer calls the
shared `initialize_array_with_constructor` helper on the first `0x20` slots in
the bucket with slot stride `0x10` and the real shared callback at `0x408600`.
The local name `ParcelBucketSlot::initialize_runtime_slot` is a recovered
meaning for that real callback target, not a dummy relocation source.

The scratch pins `END=0x443897` because the curated extent otherwise includes
post-`ret` padding and a jump into `initialize_zero_parcel_bucket_pool`.

The exact loop source is a pointer cursor plus explicit `0x800` countdown.
An indexed `for` loop compiled to a pointer-end compare instead of native's
`edi` counter.
