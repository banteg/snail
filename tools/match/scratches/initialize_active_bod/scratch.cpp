// initialize_active_bod @ 0x4085e0 (thiscall, ret)

#include "segment_cache.h"

extern void* g_active_bod_vtable; // off_497338 / data_497338

TrackRenderCacheSlot* TrackRenderCacheSlot::initialize_active_bod()
{
    initialize_bod_base();
    vtable = &g_active_bod_vtable;
    return this;
}
