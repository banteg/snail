// initialize_track_jetpack_pickup_runtime @ 0x4084d0 (thiscall, ret)

#include "track_jetpack_pickup.h"

extern void* g_jet_pack_vtable;             // off_497318 / data_497318
extern void* g_vapour_vtable;               // off_49731c / data_49731c

JetPack* JetPack::initialize_track_jetpack_pickup_runtime()
{
    initialize_bod_base();
    RenderableBod* vapour = (RenderableBod*)&vapour_a;
    vapour->initialize_renderable_bod();
    vapour->vtable = &g_vapour_vtable;
    vapour = (RenderableBod*)&vapour_b;
    vapour->initialize_renderable_bod();
    vapour->vtable = &g_vapour_vtable;
    vtable = &g_jet_pack_vtable;
    return this;
}
