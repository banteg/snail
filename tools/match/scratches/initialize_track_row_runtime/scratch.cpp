// initialize_track_row_runtime @ 0x408590 (thiscall, ret)

#include "track_attachment_types.h"

extern void* g_subrow_body_vtable; // off_497330 / data_497330

SubRow* SubRow::initialize_track_row_runtime()
{
    primary_body.initialize_renderable_bod();
    primary_body.vtable = &g_subrow_body_vtable;
    attachment_body.initialize_bod_base();
    return this;
}
