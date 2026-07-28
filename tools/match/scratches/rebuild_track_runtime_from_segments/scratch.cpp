// rebuild_track_runtime_from_segments @ 0x437de0 (thiscall, ret 0x4)

#include "game_root.h"
#include "subgame_runtime.h"
#include "segment_cache.h"


void cRSubGame::GenerateLevel(int level_index)
{
    level_mode_arg = level_index;
    SetFeatures();
    BuildColours();
    BuildLevel();
    PlaceParcels();
    SmoothTrack();
    WarnTrack();
    SlideSmoothTrack();
    CondenseTrack();
    DeSaltTrack();
    FringeEdgeTrack();

    tColour skirt_color;
    tColour* resolved_color =
        g_game->subgame.GetSkirtColour(&skirt_color);
    segment_cache.build_track_render_caches(*resolved_color);
}
