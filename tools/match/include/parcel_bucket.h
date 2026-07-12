// Shared parcel bucket pool view, cross-checked by the parcel-set and
// zero-parcel bucket initializers.
#ifndef PARCEL_BUCKET_H
#define PARCEL_BUCKET_H

#include "vector3.h"

enum {
    PARCEL_BUCKET_CAPACITY = 0x800,
    PARCEL_CANDIDATE_CAPACITY = 0x20,
    CHALLENGE_PARCEL_ROW_CAPACITY = 0x1000,
};

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
    ParcelCandidate candidates[PARCEL_CANDIDATE_CAPACITY]; // +0x000
    int candidate_count;              // +0x200
    int set_id;                       // +0x204
    int segment_index;                // +0x208
};

typedef char ParcelBucket_must_be_0x20c[
    (sizeof(ParcelBucket) == 0x20c) ? 1 : -1];

extern ParcelBucket g_parcel_set_buckets[PARCEL_BUCKET_CAPACITY];  // data_6487e8
extern ParcelBucket g_zero_parcel_buckets[PARCEL_BUCKET_CAPACITY]; // data_53d190
extern int g_challenge_parcel_rows[CHALLENGE_PARCEL_ROW_CAPACITY]; // data_6447e8

#endif
