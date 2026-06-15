// initialize_track_health_pickup_runtime @ 0x408510 (thiscall, ret)

#include "bod_types.h"

extern void* g_track_health_pickup_vtable; // off_497320 / data_497320

class TrackHealthPickupRuntime : public BodBase {
public:
    TrackHealthPickupRuntime* initialize_track_health_pickup_runtime();
};

TrackHealthPickupRuntime* TrackHealthPickupRuntime::initialize_track_health_pickup_runtime()
{
    initialize_bod_base();
    vtable = &g_track_health_pickup_vtable;
    return this;
}
