// reset_vapour @ 0x442540 (thiscall, ret 0x4)

#include "vapour.h"

void Vapour::reset_vapour(float* new_z_floor)
{
    point_count = 0;
    z_floor = new_z_floor;
    int result = list_flags;
    result &= ~0x20;
    list_flags = result;
}
