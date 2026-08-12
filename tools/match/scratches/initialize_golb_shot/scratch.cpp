// initialize_golb_shot @ 0x408690 (thiscall, ret)

#include "golb.h"

extern void* g_vapour_vtable;          // off_49731c / data_49731c
extern void* g_golb_shot_vtable;       // off_49734c / data_49734c
extern void* g_golb_noop_body_vtable;  // off_497350 / data_497350

cRSubGolb* cRSubGolb::initialize_golb_shot()
{
    this->cRBodPos::cRBodPos();
    vapour.cRBodPos::cRBodPos();
    vapour.vtable = &g_vapour_vtable;
    tertiary_body.cRBodPos::cRBodPos();
    tertiary_body.vtable = &g_golb_noop_body_vtable;
    vtable = &g_golb_shot_vtable;
    return this;
}
