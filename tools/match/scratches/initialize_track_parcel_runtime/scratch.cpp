// initialize_track_parcel_runtime @ 0x408860 (thiscall, ret)

#include "track_parcel_runtime.h"

extern void* g_parcel_vtable; // off_497364 / data_497364

Parcel* Parcel::initialize_track_parcel_runtime()
{
    initialize_bod_base();
    vtable = &g_parcel_vtable;
    return this;
}
