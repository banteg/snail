// initialize_garbage_hazard @ 0x408550 (thiscall, ret)

#include "garbage_hazard_slot.h"
#include "bod_types.h"

extern void* g_garbage_hazard_vtable; // off_497328 / data_497328

GarbageHazardSlot* GarbageHazardSlot::initialize_garbage_hazard()
{
    ((RenderableBod*)this)->initialize_renderable_bod();
    vtable = &g_garbage_hazard_vtable;
    return this;
}
