// destroy_galaxy @ 0x408c10 (thiscall, ret)

#include "border_manager.h"
#include "frontend_widget.h"

extern char* g_game_base; // data_4df904

class GalaxyRoute {
public:
    void destroy_galaxy();

    char unknown_000[0x10f74];
    FrontendWidget* pre_route_borders[3]; // +0x10f74
    char unknown_10f80[0x10f8c - 0x10f80];
    FrontendWidget* route_borders[6]; // +0x10f8c
};

void GalaxyRoute::destroy_galaxy()
{
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(pre_route_borders[1]);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(pre_route_borders[2]);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(pre_route_borders[0]);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(route_borders[0]);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(route_borders[1]);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(route_borders[3]);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(route_borders[2]);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(route_borders[4]);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(route_borders[5]);
}
