// close_galaxy_route @ 0x409bf0 (thiscall, ret)

#include "frontend_widget.h"
#include "galaxy_route_types.h"

void cRGalaxy::BoxOff()
{
    route_state = 0;
    selected_index = -1;
    borders[0]->HideInit();
    borders[1]->HideInit();
    borders[2]->HideInit();
    borders[3]->HideInit();
    borders[4]->HideInit();
    borders[5]->HideInit();
}
