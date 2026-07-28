// build_track_colours @ 0x435d40 (thiscall, ret)

#include "sprite.h"
#include "subgame_runtime.h"
#include "track_colour_banks.h"

void cRSubGame::BuildColours()
{
    for (int offset = 0;
         offset < (int)sizeof(g_loc_colour_lookup_check_black);
         offset += sizeof(tColour)) {
        ((tColour*)((char*)g_loc_colour_lookup_check_black + offset))
            ->White();
        ((tColour*)((char*)g_loc_colour_lookup_floor_slide_0.floor + offset))
            ->White();
        ((tColour*)((char*)g_loc_colour_lookup_floor_slide_0.slide_0 + offset))
            ->White();
        ((tColour*)((char*)g_loc_colour_lookup_slide_1 + offset))
            ->White();
        ((tColour*)((char*)g_loc_colour_lookup_wall + offset))->White();
        ((tColour*)((char*)g_loc_colour_lookup_trampoline + offset))
            ->White();
        ((tColour*)((char*)g_loc_colour_lookup_ramp + offset))->White();
        ((tColour*)((char*)g_loc_colour_lookup_empty + offset))->White();
        ((tColour*)((char*)g_loc_colour_lookup_path + offset))->White();
        ((tColour*)((char*)g_loc_colour_lookup_path_worm + offset))
            ->White();
        ((tColour*)((char*)g_loc_colour_lookup_path_worm + offset))
            ->White();
        ((tColour*)((char*)g_loc_colour_lookup_path_warp + offset))
            ->White();
        ((tColour*)((char*)g_loc_colour_lookup_path_warp + offset))
            ->White();
    }
}
