// initialize_track_jetpack_pickup_runtime @ 0x4084d0 (thiscall, ret)

#include "bod_types.h"

extern void* g_track_jetpack_pickup_vtable; // off_497318 / data_497318
extern void* g_track_jetpack_body_vtable;   // off_49731c / data_49731c

class TrackJetpackPickupRuntime : public BodBase {
public:
    TrackJetpackPickupRuntime* initialize_track_jetpack_pickup_runtime();

    char unknown_38[0x74 - 0x38];
    RenderableBod body_a; // +0x74
    char unknown_ec[0x108 - 0xec];
    RenderableBod body_b; // +0x108
};

TrackJetpackPickupRuntime* TrackJetpackPickupRuntime::initialize_track_jetpack_pickup_runtime()
{
    initialize_bod_base();
    body_a.initialize_renderable_bod();
    body_a.vtable = &g_track_jetpack_body_vtable;
    body_b.initialize_renderable_bod();
    body_b.vtable = &g_track_jetpack_body_vtable;
    vtable = &g_track_jetpack_pickup_vtable;
    return this;
}
