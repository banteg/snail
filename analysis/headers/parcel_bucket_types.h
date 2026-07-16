#ifndef PARCEL_BUCKET_TYPES_H
#define PARCEL_BUCKET_TYPES_H

/*
 * Narrow cross-decompiler ownership slice for the parcel-placement scratch
 * banks. Both constructor loops prove 0x800 entries with a 0x20c-byte stride;
 * the normal and survival placement consumers prove the fields below.
 */

typedef int int32_t;

#define PARCEL_BUCKET_CAPACITY 0x800
#define PARCEL_CANDIDATE_CAPACITY 0x20
#define SURVIVAL_PARCEL_GROUP_CAPACITY 0x1000

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct ParcelCandidate {
    int32_t row;
    Vec3 position;
} ParcelCandidate;

typedef struct ParcelBucket {
    ParcelCandidate candidates[PARCEL_CANDIDATE_CAPACITY];
    int32_t candidate_count;
    int32_t set_id;
    int32_t segment_index;
} ParcelBucket;

/* Cross-port original gGroup0: the digit-0 fallback scratch bank. */
extern ParcelBucket g_zero_parcel_buckets[PARCEL_BUCKET_CAPACITY];
/*
 * One-past candidate_count-lane cursor. This overlaps the independently owned
 * track-colour bank K and is only a comparison sentinel, never storage.
 */
extern char g_zero_parcel_bucket_count_lane_end;
extern int32_t
    g_parcel_group_survival_0[SURVIVAL_PARCEL_GROUP_CAPACITY];
/* Cross-port original gGroup: the positive parcel-set scratch bank. */
extern ParcelBucket g_parcel_set_buckets[PARCEL_BUCKET_CAPACITY];

#endif
