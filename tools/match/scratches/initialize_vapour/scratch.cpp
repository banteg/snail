// initialize_vapour @ 0x442500 (thiscall, ret 0x8)

#include "vapour_trail.h"

void* allocate_tracked_memory(int size, char* name);

int VapourTrail::initialize_vapour(int, int new_half_width_bits)
{
    VapourTrailOwner* owner_ptr = owner;
    half_width_bits = new_half_width_bits;
    int point_capacity = owner_ptr->max_points + 1;
    capacity = point_capacity;
    points = (TransformMatrix*)allocate_tracked_memory(point_capacity << 6, "Vapour Trail");
    return reset_vapour(0);
}
