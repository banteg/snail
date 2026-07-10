typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef int int32_t;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Color4f {
    float r;
    float g;
    float b;
    float a;
} Color4f;

typedef struct ObjectRenderVertex {
    float x;
    float y;
    float z;
    uint32_t diffuse;
    float u;
    float v;
} ObjectRenderVertex;

typedef struct TrackRenderGrid {
    uint8_t _pad_00[0x58];
} TrackRenderGrid;

typedef struct TrackRenderCacheSlot {
    uint8_t _pad_00[0x3c];
} TrackRenderCacheSlot;

typedef struct TrackRenderCacheManager {
    uint8_t _pad_00[0xa7f8];
} TrackRenderCacheManager;

void* __thiscall initialize_track_render_cache_manager(TrackRenderCacheManager* manager);
int32_t __thiscall build_track_render_caches(TrackRenderCacheManager* manager, Color4f skirt_color);
int32_t __thiscall add_track_cache_vertex(
    TrackRenderCacheManager* manager,
    void* source,
    Vec3* position,
    int32_t source_index,
    float u,
    float v,
    ObjectRenderVertex* vertices,
    int32_t* vertex_count,
    int32_t max_vertices,
    int32_t max_indices,
    uint32_t color,
    uint8_t project_uv
);
int32_t __thiscall append_track_cache_object(
    TrackRenderCacheManager* manager,
    int32_t row_index,
    void* source,
    Vec3* position,
    ObjectRenderVertex* vertices,
    int32_t* vertex_count,
    uint16_t* indices,
    int32_t* index_count,
    int32_t max_vertices,
    int32_t max_indices,
    uint32_t color,
    uint8_t project_uv
);
void __thiscall update_track_render_cache_rows(TrackRenderCacheManager* manager);
void __thiscall remove_track_render_cache_bods(TrackRenderCacheManager* manager);
int32_t __fastcall is_slide_cache_tile_family(void* cell);
int32_t __fastcall is_floor_cache_tile_family(void* cell);
int32_t __fastcall is_ramp_cache_tile_family(void* cell);
