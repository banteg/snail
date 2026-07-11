// initialize_track_row_runtime @ 0x408590 (thiscall, ret)

#include "track_attachment_types.h"

extern void* g_row_model_vtable; // off_497330 / data_497330

SubRow* SubRow::initialize_track_row_runtime()
{
    row_model.initialize_renderable_bod();
    row_model.vtable = &g_row_model_vtable;
    attachment_body.initialize_bod_base();
    return this;
}
