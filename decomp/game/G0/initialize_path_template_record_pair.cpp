// initialize_path_template_record_pair @ 0x4085c0 (thiscall, ret)

#include "track_attachment_types.h"

extern void* g_path_template_record_vtable; // off_497334 / data_497334

cRPath* cRPath::initialize_path_template_record_pair()
{
    this->cRBod::cRBod();
    fringe_mesh_bod.cRBod::cRBod();
    vtable = &g_path_template_record_vtable;
    return this;
}
