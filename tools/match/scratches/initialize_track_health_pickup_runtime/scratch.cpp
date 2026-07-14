// initialize_track_health_pickup_runtime @ 0x408510 (thiscall, ret)

#include "track_health_pickup.h"

extern void* g_sub_health_vtable; // off_497320 / data_497320

SubHealth* SubHealth::initialize_track_health_pickup_runtime()
{
    initialize_bod_base();
    vtable = &g_sub_health_vtable;
    return this;
}
