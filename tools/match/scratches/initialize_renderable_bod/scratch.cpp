// initialize_renderable_bod @ 0x42f650 (thiscall, ret)

#include "bod_types.h"

extern void* g_renderable_bod_vtable; // off_497500 / data_497500

RenderableBod* RenderableBod::initialize_renderable_bod()
{
    initialize_bod_base();
    vtable = &g_renderable_bod_vtable;
    list_flags = BOD_FLAG_VIEWPORT_1 | BOD_FLAG_USE_TRANSFORM
        | BOD_FLAG_RENDER_ENABLED;
    transform.set_matrix_identity();
    return this;
}
