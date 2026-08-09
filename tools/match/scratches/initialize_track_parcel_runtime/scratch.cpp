// initialize_track_parcel_runtime @ 0x408860 (thiscall, ret)
// Authored owner: cRParcel::cRParcel().

#include "track_parcel_runtime.h"

extern void* g_parcel_vtable; // off_497364 / data_497364

cRParcel::cRParcel()
{
    initialize_bod_base();
    vtable = &g_parcel_vtable;
}
