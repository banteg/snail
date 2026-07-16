// initialize_renderable_bod @ 0x42f650 (thiscall, ret)

#include "bod_types.h"

RenderableBod* RenderableBod::initialize_renderable_bod()
{
    initialize_bod_base();
    vtable = &g_renderable_bod_vtable;
    list_flags = RENDER_SCENE_PLAYER_0 | BOD_FLAG_USE_TRANSFORM
        | BOD_FLAG_RENDER_ENABLED;
    transform.set_matrix_identity();
    return this;
}
