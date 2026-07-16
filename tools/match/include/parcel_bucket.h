// Shared parcel bucket pool view, cross-checked by the parcel-set and
// zero-parcel bucket initializers.
#ifndef PARCEL_BUCKET_H
#define PARCEL_BUCKET_H

#include "vector3.h"

enum {
    PARCEL_BUCKET_CAPACITY = 0x800,
    PARCEL_CANDIDATE_CAPACITY = 0x20,
    SURVIVAL_PARCEL_GROUP_CAPACITY = 0x1000,
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

// Cross-port originals: gGroup is the parcel-set bank and gGroup0 is the
// digit-0 fallback bank. The semantic names retain each bank's actual role.
extern ParcelBucket g_parcel_set_buckets[PARCEL_BUCKET_CAPACITY];  // data_6487e8
extern ParcelBucket g_zero_parcel_buckets[PARCEL_BUCKET_CAPACITY]; // data_53d190
// One-past candidate_count-lane cursor for g_zero_parcel_buckets. The address
// is used as a signed pointer-walk sentinel and is never dereferenced.
extern char g_zero_parcel_bucket_count_lane_end; // data_643390
// Cross-port original symbol: gParcelGroupSurvival0.
extern int g_parcel_group_survival_0[SURVIVAL_PARCEL_GROUP_CAPACITY]; // data_6447e8

#endif
