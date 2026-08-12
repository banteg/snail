// initialize_garbage_hazard @ 0x408550 (thiscall, ret)
// Authored owner: cRSubGarbage::cRSubGarbage().

#include "garbage_hazard_slot.h"

extern void* g_sub_garbage_vtable; // off_497328 / data_497328

cRSubGarbage::cRSubGarbage()
{
    vtable = &g_sub_garbage_vtable;
}
