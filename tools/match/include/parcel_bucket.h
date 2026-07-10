// Shared parcel bucket pool view, cross-checked by the parcel-set and
// zero-parcel bucket initializers.
#ifndef PARCEL_BUCKET_H
#define PARCEL_BUCKET_H

#include "vector3.h"

class ParcelCandidate {
public:
    void noop_runtime_slot_constructor(); // sub_408600

    int row;          // +0x00, row within the source segment
    Vector3 position; // +0x04, authored or glyph-derived local position
};

typedef void (ParcelCandidate::*ParcelCandidateConstructor)();

void __stdcall initialize_array_with_constructor(
    ParcelCandidate* base,
    int stride,
    int count,
    ParcelCandidateConstructor constructor);

struct ParcelBucket {
    ParcelCandidate candidates[0x20]; // +0x000
    int candidate_count;              // +0x200
    int set_id;                       // +0x204
    int segment_index;                // +0x208
};

typedef char ParcelBucket_must_be_0x20c[
    (sizeof(ParcelBucket) == 0x20c) ? 1 : -1];

extern ParcelBucket g_parcel_set_buckets[0x800];  // data_6487e8
extern ParcelBucket g_zero_parcel_buckets[0x800]; // data_53d190

#endif
