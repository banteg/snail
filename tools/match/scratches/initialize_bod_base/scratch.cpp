// initialize_bod_base @ 0x42f5f0 (thiscall, ret)

#include "bod_types.h"

BodBase* BodBase::initialize_bod_base()
{
    color.noop_this_constructor();
    vtable = &g_bod_base_vtable;
    list_flags = RENDER_SCENE_PLAYER_0 | BOD_FLAG_RENDER_ENABLED;
    color.store_color4f(1.0f, 1.0f, 1.0f, 1.0f);
    ++g_bod_base_init_count;
    position.z = 0.0f;
    position.y = 0.0f;
    position.x = 0.0f;
    render_arg_1c = 0;
    render_arg_20 = 0.0f;
    return this;
}
