typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;

struct TrackRowCell;
struct RenderObjectTextureGroups;

typedef struct TrackRenderGrid {
    uint8_t _pad_00[0x58];
} TrackRenderGrid;

typedef struct TrackRenderCacheSlot {
    uint8_t _pad_00[0x3c];
} TrackRenderCacheSlot;

typedef struct TrackRenderCacheManager {
    uint8_t _pad_00[0x8];
} TrackRenderCacheManager;

void* __fastcall initialize_track_render_cache_manager(TrackRenderCacheManager* manager);
int32_t __fastcall build_track_render_caches(TrackRenderCacheManager* manager);
void __fastcall update_track_render_cache_rows(TrackRenderCacheManager* manager);
void __fastcall remove_track_render_cache_bods(TrackRenderCacheManager* manager);
int32_t __fastcall is_slide_cache_tile_family(struct TrackRowCell* cell);
int32_t __fastcall is_floor_cache_tile_family(struct TrackRowCell* cell);
int32_t __fastcall is_ramp_cache_tile_family(struct TrackRowCell* cell);
