// initialize_track_speedup_runtime @ 0x4084b0 (thiscall, ret)

#include "track_speedup.h"

extern void* g_track_speedup_vtable; // off_497314 / data_497314

TrackSpeedupRuntime* TrackSpeedupRuntime::initialize_track_speedup_runtime()
{
    ((RenderableBod*)this)->initialize_renderable_bod();
    unknown_00 = (int)&g_track_speedup_vtable;
    return this;
}
