// initialize_track_health_pickup_runtime @ 0x408510 (thiscall, ret)

#include "bod_types.h"
#include "track_health_pickup.h"

extern void* g_track_health_pickup_vtable; // off_497320 / data_497320

TrackHealthPickup* TrackHealthPickup::initialize_track_health_pickup_runtime()
{
    ((BodBase*)this)->initialize_bod_base();
    ((BodBase*)this)->vtable = &g_track_health_pickup_vtable;
    return this;
}
