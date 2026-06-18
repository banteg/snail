// rebuild_track_runtime_from_segments @ 0x437de0 (thiscall, ret 0x4)

#include "subgame_runtime.h"
#include "track_render_cache.h"

extern char* g_game_base; // data_4df904

int SubgameRuntime::rebuild_track_runtime_from_segments(int level_index)
{
    level_mode_arg = level_index;
    set_subgame_features();
    build_track_colours();
    populate_runtime_track_cells_from_segments();
    place_parcels_on_track();
    select_track_tile_edge_variants();
    promote_track_tiles_to_fringe_variants();
    harmonize_center_lane_floor_slide_variants();
    merge_track_tile_runs();
    mark_track_warning_zones();
    build_track_fringe_objects();

    Color4f skirt_color;
    Color4f* resolved_color =
        ((SubgameRuntime*)(g_game_base + 0x74618))->get_track_skirt_color(&skirt_color);
    return ((TrackRenderCacheManager*)((char*)this + 0x5c))->build_track_render_caches(*resolved_color);
}
