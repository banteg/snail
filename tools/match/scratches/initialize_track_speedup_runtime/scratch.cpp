// initialize_track_speedup_runtime @ 0x4084b0 (thiscall, ret)
// Authored owner: cRSubSpeedUp::cRSubSpeedUp().

#include "track_speedup.h"

extern void* g_sub_speed_up_vtable; // off_497314 / data_497314

cRSubSpeedUp::cRSubSpeedUp()
{
    initialize_renderable_bod();
    vtable = &g_sub_speed_up_vtable;
}
