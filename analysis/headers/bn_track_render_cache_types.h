typedef unsigned char uint8_t;

typedef struct TrackRenderGrid {
    uint8_t _pad_00[0x58];
} TrackRenderGrid;

typedef struct TrackRenderCacheSlot {
    uint8_t _pad_00[0x3c];
} TrackRenderCacheSlot;

typedef struct SegmentCache {
    uint8_t _pad_00[0xa7f8];
} SegmentCache;
