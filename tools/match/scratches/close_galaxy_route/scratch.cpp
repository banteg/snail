// close_galaxy_route @ 0x409bf0 (thiscall, ret)

#include "frontend_widget.h"
#include "galaxy_route_types.h"

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
