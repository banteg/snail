// initialize_garbage_hazard @ 0x408550 (thiscall, ret)

#include "garbage_hazard_slot.h"

extern void* g_sub_garbage_vtable; // off_497328 / data_497328

SubGarbage* SubGarbage::initialize_garbage_hazard()
{
    initialize_renderable_bod();
    vtable = &g_sub_garbage_vtable;
    return this;
}
