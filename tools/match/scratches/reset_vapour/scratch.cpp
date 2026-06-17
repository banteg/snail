// reset_vapour @ 0x442540 (thiscall, ret 0x4)

#include "vapour_trail.h"

int VapourTrail::reset_vapour(int new_z_floor)
{
    point_count = 0;
    z_floor = new_z_floor;
    int result = flags;
    result &= ~0x20;
    flags = result;
    return result;
}
