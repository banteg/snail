// initialize_bod_base @ 0x42f5f0 (thiscall, ret)

#include "bod_types.h"

extern void* g_bod_base_vtable; // off_4974fc / data_4974fc
extern int g_bod_base_init_count; // data_50331c

BodBase* BodBase::initialize_bod_base()
{
    color.noop_this_constructor();
    vtable = &g_bod_base_vtable;
    list_flags = BOD_FLAG_VIEWPORT_1 | BOD_FLAG_RENDER_ENABLED;
    color.store_color4f(1.0f, 1.0f, 1.0f, 1.0f);
    ++g_bod_base_init_count;
    position.z = 0.0f;
    position.y = 0.0f;
    position.x = 0.0f;
    render_arg_1c = 0;
    render_arg_20 = 0.0f;
    return this;
}
