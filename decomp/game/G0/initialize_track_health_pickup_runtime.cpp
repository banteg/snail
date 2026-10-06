// initialize_track_health_pickup_runtime @ 0x408510 (thiscall, ret)
// Authored owner: cRSubHealth::cRSubHealth().

#include "track_health_pickup.h"

extern void* g_sub_health_vtable; // off_497320 / data_497320

cRSubHealth::cRSubHealth()
{
    vtable = &g_sub_health_vtable;
}
