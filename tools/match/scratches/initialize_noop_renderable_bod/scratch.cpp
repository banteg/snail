// initialize_noop_renderable_bod @ 0x408040 (thiscall)

#include "bod_types.h"

cRBodPos* cRBodPos::initialize_noop_renderable_bod()
{
    initialize_renderable_bod();
    vtable = &g_noop_runtime_callback_table;
    return this;
}
