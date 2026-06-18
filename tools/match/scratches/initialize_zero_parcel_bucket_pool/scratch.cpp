// initialize_zero_parcel_bucket_pool @ 0x4438b0 (ret)

#include "parcel_bucket.h"

extern ParcelBucket g_zero_parcel_buckets[0x800]; // data_53d190

void initialize_zero_parcel_bucket_pool()
{
    ParcelBucket* bucket = g_zero_parcel_buckets;
    int count = 0x800;
    do {
        initialize_array_with_constructor(
            bucket->slots,
            0x10,
            0x20,
            &ParcelBucketSlot::noop_runtime_slot_constructor);
        ++bucket;
    } while (--count != 0);
}
