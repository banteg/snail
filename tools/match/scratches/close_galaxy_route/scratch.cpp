// close_galaxy_route @ 0x409bf0 (thiscall, ret)

#include "frontend_widget.h"

class GalaxyRoute {
public:
    void close_galaxy_route();

    char unknown_000[0x8];
    int route_state; // +0x08
    char unknown_00c[0x10f80 - 0x00c];
    int selected_index; // +0x10f80, -1 sentinel
    char unknown_10f84[0x10f8c - 0x10f84];
    FrontendWidget* borders[6]; // +0x10f8c
};

void GalaxyRoute::close_galaxy_route()
{
    route_state = 0;
    selected_index = -1;
    borders[0]->hide_border_init();
    borders[1]->hide_border_init();
    borders[2]->hide_border_init();
    borders[3]->hide_border_init();
    borders[4]->hide_border_init();
    borders[5]->hide_border_init();
}
