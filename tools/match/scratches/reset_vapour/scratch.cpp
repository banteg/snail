// reset_vapour @ 0x442540 (thiscall, ret 0x4)

#include "vapour_trail.h"

int VapourTrail::reset_vapour(int new_mode)
{
    point_count = 0;
    mode = new_mode;
    int result = flags;
    result &= ~0x20;
    flags = result;
    return result;
}
