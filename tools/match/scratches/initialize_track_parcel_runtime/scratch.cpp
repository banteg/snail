// initialize_track_parcel_runtime @ 0x408860 (thiscall, ret)

#include "track_parcel_runtime.h"

extern void* g_track_parcel_vtable; // off_497364 / data_497364

TrackParcelRuntime* TrackParcelRuntime::initialize_track_parcel_runtime()
{
    initialize_bod_base();
    vtable = &g_track_parcel_vtable;
    return this;
}
