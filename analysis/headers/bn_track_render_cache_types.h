typedef unsigned char uint8_t;

typedef struct SubgameRuntime SubgameRuntime;

typedef struct TrackRenderCacheSlot {
    uint8_t _pad_00[0x3c];
} TrackRenderCacheSlot;

/*
 * Analysis-only manager-relative view used by the constructor's slot walk.
 * The native cursor advances from SegmentCache + n * 0x3c and reaches the
 * embedded slot through +0x58; the prefix aliases manager storage.
 */
typedef struct TrackRenderCacheSlotCursor {
    uint8_t manager_prefix[0x58];
    TrackRenderCacheSlot slot;
} TrackRenderCacheSlotCursor;

typedef struct SegmentCache {
    uint8_t _pad_00[0xa7f8];
} SegmentCache;
