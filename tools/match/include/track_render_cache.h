// Track render cache manager, partial.
#ifndef TRACK_RENDER_CACHE_H
#define TRACK_RENDER_CACHE_H

#include "bod_types.h"
#include "sprite.h"

struct TrackRenderGrid;

struct TrackRenderCacheSlot {
    BodBase bod;     // +0x00, render object pointer is BodBase::object at +0x24
    int unknown_38;  // +0x38, slot stride padding/state
};

typedef char TrackRenderCacheSlot_must_be_0x3c[
    (sizeof(TrackRenderCacheSlot) == 0x3c) ? 1 : -1];

class TrackRenderCacheManager {
public:
    int build_track_render_caches(Color4f skirt_color); // @ 0x433220
    void update_track_render_cache_rows();              // @ 0x433b30
    int remove_track_render_cache_bods();               // @ 0x433f20

    int max_vertex_counts[5]; // +0x00
    int max_index_counts[5];  // +0x14
    TrackRenderGrid* track_render_grid; // +0x28
    char unknown_2c[0x58 - 0x2c];
    TrackRenderCacheSlot slots[0x8f][5]; // +0x58
    float build_cache_row_base; // +0xa7ec
    float next_cache_row_z; // +0xa7f0
    int next_cache_row_index; // +0xa7f4
};

#endif
