// initialize_vapour @ 0x442500 (thiscall, ret 0x8)

#include "object_render_types.h"
#include "vapour.h"

void* allocate_tracked_memory(int size, char* name);

void Vapour::initialize_vapour(Object*, float new_half_width)
{
    Object* owner_ptr = owner;
    half_width = new_half_width;
    int point_capacity = owner_ptr->facequad_count + 1;
    capacity = point_capacity;
    points = (TransformMatrix*)allocate_tracked_memory(point_capacity << 6, "Vapour Trail");
    reset_vapour(0);
}
