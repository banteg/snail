// initialize_track_row_runtime @ 0x408590 (thiscall, ret)

#include "bod_types.h"

extern void* g_track_row_vtable; // off_497330 / data_497330

class TrackRowRuntime {
public:
    TrackRowRuntime* initialize_track_row_runtime();

    void* vtable; // +0x00
    RenderableBod row_body; // +0x04
    char unknown_7c[0xb0 - 0x7c];
    BodBase aux_body; // +0xb0
};

TrackRowRuntime* TrackRowRuntime::initialize_track_row_runtime()
{
    row_body.initialize_renderable_bod();
    row_body.vtable = &g_track_row_vtable;
    aux_body.initialize_bod_base();
    return this;
}
