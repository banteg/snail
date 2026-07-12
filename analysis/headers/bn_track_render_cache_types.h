typedef unsigned char uint8_t;

typedef struct SubgameRuntime SubgameRuntime;

typedef struct TrackRenderCacheSlot {
    uint8_t _pad_00[0x3c];
} TrackRenderCacheSlot;

typedef struct SegmentCache {
    uint8_t _pad_00[0xa7f8];
} SegmentCache;
