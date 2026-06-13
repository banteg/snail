// initialize_parcel_set_bucket_pool @ 0x443870 (ret)

class ParcelBucketSlot {
public:
    void initialize_runtime_slot(); // sub_408600

    char unknown_00[0x10];
};

typedef void (ParcelBucketSlot::*ParcelBucketSlotConstructor)();

void __stdcall initialize_array_with_constructor(
    ParcelBucketSlot* base,
    int stride,
    int count,
    ParcelBucketSlotConstructor constructor);

struct ParcelBucket {
    ParcelBucketSlot slots[0x20]; // +0x000
    char unknown_200[0x20c - 0x200];
};

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
