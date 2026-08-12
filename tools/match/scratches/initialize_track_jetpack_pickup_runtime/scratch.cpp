// initialize_track_jetpack_pickup_runtime @ 0x4084d0 (thiscall, ret)
// Authored owner: cRJetPack::cRJetPack().

#include "track_jetpack_pickup.h"

extern void* g_jet_pack_vtable;             // off_497318 / data_497318
extern void* g_vapour_vtable;               // off_49731c / data_49731c

inline cRVapour::cRVapour()
{
    vtable = &g_vapour_vtable;
}

cRJetPack::cRJetPack()
{
    vtable = &g_jet_pack_vtable;
}
