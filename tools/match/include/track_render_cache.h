// Track render cache manager, partial.
#ifndef TRACK_RENDER_CACHE_H
#define TRACK_RENDER_CACHE_H

#include "bod_types.h"
#include "sprite.h"

struct TrackRenderGrid;
class SubgameRuntime;
struct ObjectRenderVertex;
struct Object;

struct TrackRenderCacheSlot {
    // The manager owns the BOD node. BodBase::object is a handle allocated
    // from the global ObjectList and retained for the manager lifetime.
    BodBase bod;          // +0x00, object handle at +0x24
    float cache_row_base; // +0x38, shared by all five families in one cache row
};

typedef char TrackRenderCacheSlot_must_be_0x3c[
    (sizeof(TrackRenderCacheSlot) == 0x3c) ? 1 : -1];

class TrackRenderCacheManager {
public:
    void* initialize_track_render_cache_manager();       // @ 0x433060
    int build_track_render_caches(Color4f skirt_color); // @ 0x433220
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
        int max_indices,
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

    unsigned int skirt_color_bgra; // +0x00, packed from the level fringe color
    int max_vertex_counts[5]; // +0x04
    int max_index_counts[5];  // +0x18
    ObjectRenderVertex* shared_vertex_buffers[5]; // +0x2c, owned tracked allocations
    unsigned short* shared_index_buffers[5]; // +0x40, owned tracked allocations
    union {
        SubgameRuntime* owner_subgame; // +0x54, borrowed enclosing runtime
        TrackRenderGrid* track_render_grid; // codegen view of the same runtime
    };
    TrackRenderCacheSlot slots[0x8f][5]; // +0x58
    float build_cache_row_base; // +0xa7ec
    float next_cache_row_z; // +0xa7f0
    int next_cache_row_index; // +0xa7f4
};

typedef char TrackRenderCacheManager_must_be_0xa7f8[
    (sizeof(TrackRenderCacheManager) == 0xa7f8) ? 1 : -1];

#endif
