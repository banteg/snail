// initialize_track_ring_or_special_effect_runtime @ 0x408570 (thiscall, ret)

#include "bod_types.h"
#include "ring_special_effect_types.h"

extern void* g_sub_ring_vtable; // off_49732c / data_49732c

SubRing* SubRing::initialize_track_ring_or_special_effect_runtime()
{
    initialize_renderable_bod();
    vtable = &g_sub_ring_vtable;
    return this;
}
