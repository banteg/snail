// destroy_galaxy @ 0x408c10 (thiscall, ret)

#include "border_manager.h"
#include "frontend_widget.h"
#include "galaxy_route_types.h"

extern char* g_game_base; // data_4df904

void GalaxyRoute::destroy_galaxy()
{
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(pre_route_borders[1]);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(pre_route_borders[2]);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(pre_route_borders[0]);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(borders[0]);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(borders[1]);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(borders[3]);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(borders[2]);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(borders[4]);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(borders[5]);
}
