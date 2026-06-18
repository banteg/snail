// Shared parcel bucket pool view, cross-checked by the parcel-set and
// zero-parcel bucket initializers.
#ifndef PARCEL_BUCKET_H
#define PARCEL_BUCKET_H

class ParcelBucketSlot {
public:
    void noop_runtime_slot_constructor(); // sub_408600

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

#endif
