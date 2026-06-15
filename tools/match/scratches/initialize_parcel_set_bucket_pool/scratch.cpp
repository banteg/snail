// initialize_parcel_set_bucket_pool @ 0x443870 (ret)

#include "parcel_bucket.h"

extern ParcelBucket g_parcel_set_buckets[0x800]; // data_6487e8

void initialize_parcel_set_bucket_pool()
{
    ParcelBucket* bucket = g_parcel_set_buckets;
    int count = 0x800;
    do {
        initialize_array_with_constructor(
            bucket->slots,
            0x10,
            0x20,
            &ParcelBucketSlot::initialize_runtime_slot);
        ++bucket;
    } while (--count != 0);
}
