// initialize_noop_renderable_bod @ 0x408040 (thiscall)

#include "bod_types.h"

extern void* g_noop_runtime_callback_table; // data_4972b0

RenderableBod* RenderableBod::initialize_noop_renderable_bod()
{
    initialize_renderable_bod();
    vtable = &g_noop_runtime_callback_table;
    return this;
}
