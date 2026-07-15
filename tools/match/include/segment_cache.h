// Authored cRSegmentCache owner embedded in SubgameRuntime. The runtime size
// ledger fixes its 0xa7f8-byte extent; the complete field layout is recovered
// from its constructor, cache builder, row updater, and teardown methods.
#ifndef SEGMENT_CACHE_H
#define SEGMENT_CACHE_H

#include "bod_types.h"
#include "sprite.h"

class SubgameRuntime;
struct ObjectRenderVertex;
struct Object;

// Native debug names and all five dispatch arms agree on this family order.
enum TrackRenderCacheFamily {
    TRACK_RENDER_CACHE_FLOOR = 0,
    TRACK_RENDER_CACHE_SLIDE = 1,
    TRACK_RENDER_CACHE_WARNING = 2,
    TRACK_RENDER_CACHE_RAMP = 3,
    TRACK_RENDER_CACHE_FRINGE = 4,
    TRACK_RENDER_CACHE_FAMILY_COUNT = 5,
};

enum {
    TRACK_RENDER_CACHE_ROW_COUNT = 0x8f,
};

struct TrackRenderCacheSlot {
    // The manager owns the BOD node. BodBase::object is a handle allocated
    // from the global ObjectList and retained for the manager lifetime.
    BodBase bod;          // +0x00, object handle at +0x24
    float cache_row_base; // +0x38, shared by all five families in one cache row
};

typedef char TrackRenderCacheSlot_must_be_0x3c[
    (sizeof(TrackRenderCacheSlot) == 0x3c) ? 1 : -1];

class SegmentCache {
public:
    void initialize_track_render_cache_manager();       // @ 0x433060
    void build_track_render_caches(tColour skirt_color); // @ 0x433220
    void update_track_render_cache_rows();              // @ 0x433b30
    void remove_track_render_cache_bods();              // @ 0x433f20
    int add_track_cache_vertex(
        Object* source,
        Vector3* position,
        int source_index,
        float u,
        float v,
        ObjectRenderVertex* vertices,
        int* vertex_count,
        int max_vertices,
        int unused_max_indices,
        unsigned int color,
        unsigned char project_uv); // @ 0x433830
    int append_track_cache_object(
        int row_index,
        Object* source,
        Vector3* position,
        ObjectRenderVertex* vertices,
        int* vertex_count,
        unsigned short* indices,
        int* index_count,
        int max_vertices,
        int max_indices,
        unsigned int color,
        unsigned char project_uv); // @ 0x433960

    tColourSmall skirt_color_bgra; // +0x00, packed from the level fringe color
    int max_vertex_counts[TRACK_RENDER_CACHE_FAMILY_COUNT]; // +0x04
    int max_index_counts[TRACK_RENDER_CACHE_FAMILY_COUNT];  // +0x18
    ObjectRenderVertex*
        shared_vertex_buffers[TRACK_RENDER_CACHE_FAMILY_COUNT]; // +0x2c
    unsigned short*
        shared_index_buffers[TRACK_RENDER_CACHE_FAMILY_COUNT]; // +0x40
    SubgameRuntime* owner_subgame; // +0x54, borrowed enclosing runtime
    TrackRenderCacheSlot
        slots[TRACK_RENDER_CACHE_ROW_COUNT][TRACK_RENDER_CACHE_FAMILY_COUNT]; // +0x58
    float build_cache_row_base; // +0xa7ec
    float next_cache_row_z; // +0xa7f0
    int next_cache_row_index; // +0xa7f4
};

typedef char SegmentCache_must_be_0xa7f8[
    (sizeof(SegmentCache) == 0xa7f8) ? 1 : -1];

#endif
