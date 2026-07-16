// build_track_colours @ 0x435d40 (thiscall, ret)

#include "sprite.h"
#include "subgame_runtime.h"
#include "track_colour_banks.h"

void SubgameRuntime::build_track_colours()
{
    for (int offset = 0;
         offset < (int)sizeof(g_loc_colour_lookup_check_black);
         offset += sizeof(tColour)) {
        ((tColour*)((char*)g_loc_colour_lookup_check_black + offset))
            ->set_color_white();
        ((tColour*)((char*)g_loc_colour_lookup_floor_slide_0.floor + offset))
            ->set_color_white();
        ((tColour*)((char*)g_loc_colour_lookup_floor_slide_0.slide_0 + offset))
            ->set_color_white();
        ((tColour*)((char*)g_loc_colour_lookup_slide_1 + offset))
            ->set_color_white();
        ((tColour*)((char*)g_loc_colour_lookup_wall + offset))->set_color_white();
        ((tColour*)((char*)g_loc_colour_lookup_trampoline + offset))
            ->set_color_white();
        ((tColour*)((char*)g_loc_colour_lookup_ramp + offset))->set_color_white();
        ((tColour*)((char*)g_loc_colour_lookup_empty + offset))->set_color_white();
        ((tColour*)((char*)g_loc_colour_lookup_path + offset))->set_color_white();
        ((tColour*)((char*)g_loc_colour_lookup_path_worm + offset))
            ->set_color_white();
        ((tColour*)((char*)g_loc_colour_lookup_path_worm + offset))
            ->set_color_white();
        ((tColour*)((char*)g_loc_colour_lookup_path_warp + offset))
            ->set_color_white();
        ((tColour*)((char*)g_loc_colour_lookup_path_warp + offset))
            ->set_color_white();
    }
}
