// initialize_vapour @ 0x442500 (thiscall, ret 0x8)

#include "vapour_trail.h"

void* allocate_tracked_memory(int size, char* name);

int VapourTrail::initialize_vapour(int, int new_point_stride)
{
    VapourTrailOwner* owner_ptr = owner;
    point_stride = new_point_stride;
    int point_capacity = owner_ptr->max_points + 1;
    capacity = point_capacity;
    points = allocate_tracked_memory(point_capacity << 6, "Vapour Trail");
    return reset_vapour(0);
}
