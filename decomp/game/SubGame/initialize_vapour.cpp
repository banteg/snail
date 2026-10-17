// initialize_vapour @ 0x442500 (thiscall, ret 0x8)

#include "object_render_types.h"
#include "tracked_allocation_stack.h"
#include "vapour.h"

void cRVapour::Init(cRObject*, float new_half_width)
{
    Object* owner_ptr = object;
    half_width = new_half_width;
    int point_capacity = owner_ptr->facequad_count + 1;
    capacity = point_capacity;
    points = (TransformMatrix*)allocate_tracked_memory(point_capacity << 6, "Vapour Trail");
    ReSet(0);
}
