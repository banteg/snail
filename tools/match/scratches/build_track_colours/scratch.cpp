// build_track_colours @ 0x435d40 (thiscall, ret)

#include "sprite.h"
#include "subgame_runtime.h"
#include "track_colour_banks.h"

void SubgameRuntime::build_track_colours()
{
    for (int offset = 0;
         offset < (int)sizeof(g_track_colour_bank_a);
         offset += sizeof(tColour)) {
        ((tColour*)((char*)g_track_colour_bank_a + offset))->set_color_white();
        ((tColour*)((char*)g_track_colour_banks_b_c + offset))->set_color_white();
        ((tColour*)((char*)g_track_colour_banks_b_c
            + sizeof(g_track_colour_bank_a) + offset))
            ->set_color_white();
        ((tColour*)((char*)g_track_colour_bank_d + offset))->set_color_white();
        ((tColour*)((char*)g_track_colour_bank_e + offset))->set_color_white();
        ((tColour*)((char*)g_track_colour_bank_f + offset))->set_color_white();
        ((tColour*)((char*)g_track_colour_bank_g + offset))->set_color_white();
        ((tColour*)((char*)g_track_colour_bank_h + offset))->set_color_white();
        ((tColour*)((char*)g_track_colour_bank_i + offset))->set_color_white();
        ((tColour*)((char*)g_track_colour_bank_j + offset))->set_color_white();
        ((tColour*)((char*)g_track_colour_bank_j + offset))->set_color_white();
        ((tColour*)((char*)g_track_colour_bank_k + offset))->set_color_white();
        ((tColour*)((char*)g_track_colour_bank_k + offset))->set_color_white();
    }
}
