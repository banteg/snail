// initialize_border_record @ 0x408410 (thiscall, ret)

#include "border_manager.h"

extern void* g_frontend_widget_vtable; // off_497308 / data_497308

BorderRecord* BorderRecord::initialize_border_record()
{
    initialize_bod_base();
    color_06c.noop_this_constructor();
    color_1ac.noop_this_constructor();
    color_1bc.noop_this_constructor();
    color_1cc.noop_this_constructor();
    color_1dc.noop_this_constructor();
    color_1ec.noop_this_constructor();
    color_1fc.noop_this_constructor();
    vtable = &g_frontend_widget_vtable;
    return this;
}
