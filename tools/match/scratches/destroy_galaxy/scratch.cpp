// destroy_galaxy @ 0x408c10 (thiscall, ret)

#include "frontend_widget.h"
#include "galaxy_route_types.h"
#include "game_root.h"

extern GameRoot* g_game; // data_4df904

void Galaxy::destroy_galaxy()
{
    g_game->border_manager.kill_border(pre_route_borders[1]);
    g_game->border_manager.kill_border(pre_route_borders[2]);
    g_game->border_manager.kill_border(pre_route_borders[0]);
    g_game->border_manager.kill_border(borders[0]);
    g_game->border_manager.kill_border(borders[1]);
    g_game->border_manager.kill_border(borders[3]);
    g_game->border_manager.kill_border(borders[2]);
    g_game->border_manager.kill_border(borders[4]);
    g_game->border_manager.kill_border(borders[5]);
}
