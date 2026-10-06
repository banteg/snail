// update_galaxy_route_record @ 0x409bd0 (thiscall, ret)

#include "galaxy_route_types.h"

void cRGalaxyStar::AI()
{
    record.route_tint_alpha =
        (record.highlight_target - record.route_tint_alpha) * 0.1f +
        record.route_tint_alpha;
}
