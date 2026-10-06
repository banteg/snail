// initialize_noop_renderable_bod @ 0x408040 (thiscall)

#include "bod_types.h"

cRBodPos* cRBodPos::initialize_noop_renderable_bod()
{
    this->cRBodPos::cRBodPos();
    vtable = &g_noop_runtime_callback_table;
    return this;
}
