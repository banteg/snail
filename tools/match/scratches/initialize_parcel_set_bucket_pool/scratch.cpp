// initialize_parcel_set_bucket_pool @ 0x443870 (ret)

#include "parcel_bucket.h"

void initialize_parcel_set_bucket_pool()
{
    ParcelBucket* bucket = g_parcel_set_buckets;
    int count = 0x800;
    do {
        initialize_array_with_constructor(
            bucket->candidates,
            0x10,
            0x20,
            &ParcelCandidate::noop_runtime_slot_constructor);
        ++bucket;
    } while (--count != 0);
}
