// initialize_track_jetpack_pickup_runtime @ 0x4084d0 (thiscall, ret)

#include "track_jetpack_pickup.h"

extern void* g_track_jetpack_pickup_vtable; // off_497318 / data_497318
extern void* g_track_jetpack_body_vtable;   // off_49731c / data_49731c

TrackJetpackPickup* TrackJetpackPickup::initialize_track_jetpack_pickup_runtime()
{
    ((BodBase*)this)->initialize_bod_base();
    body_a.initialize_renderable_bod();
    body_a.vtable = &g_track_jetpack_body_vtable;
    body_b.initialize_renderable_bod();
    body_b.vtable = &g_track_jetpack_body_vtable;
    unknown_00 = (int)&g_track_jetpack_pickup_vtable;
    return this;
}
