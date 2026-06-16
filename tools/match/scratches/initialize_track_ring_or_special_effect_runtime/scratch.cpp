// initialize_track_ring_or_special_effect_runtime @ 0x408570 (thiscall, ret)

#include "bod_types.h"
#include "ring_special_effect_types.h"

extern void* g_track_ring_or_special_effect_vtable; // off_49732c / data_49732c

RingOrSpecialEffectParent*
RingOrSpecialEffectParent::initialize_track_ring_or_special_effect_runtime()
{
    ((RenderableBod*)this)->initialize_renderable_bod();
    ((RenderableBod*)this)->vtable = &g_track_ring_or_special_effect_vtable;
    return this;
}
