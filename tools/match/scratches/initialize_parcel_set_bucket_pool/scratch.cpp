// initialize_parcel_set_bucket_pool @ 0x443870 (ret)

#include "parcel_bucket.h"

void initialize_parcel_set_bucket_pool()
{
    ParcelBucket* bucket = g_parcel_set_buckets;
    int count = PARCEL_BUCKET_CAPACITY;
    do {
        initialize_array_with_constructor(
            bucket->candidates,
            sizeof(ParcelCandidate),
            PARCEL_CANDIDATE_CAPACITY,
            &ParcelCandidate::noop_runtime_slot_constructor);
        ++bucket;
    } while (--count != 0);
}
