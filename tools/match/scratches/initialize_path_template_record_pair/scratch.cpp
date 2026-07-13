// initialize_path_template_record_pair @ 0x4085c0 (thiscall, ret)

#include "track_attachment_types.h"

extern void* g_path_template_record_vtable; // off_497334 / data_497334

Path* Path::initialize_path_template_record_pair()
{
    initialize_bod_base();
    fringe_mesh_bod.initialize_bod_base();
    vtable = &g_path_template_record_vtable;
    return this;
}
