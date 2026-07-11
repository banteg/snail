// initialize_fringe_object @ 0x408650 (thiscall, ret)

#include "fringe_object.h"

extern void* g_fringe_vtable; // off_497344 / data_497344

Fringe* Fringe::initialize_fringe_object()
{
    initialize_bod_base();
    vtable = &g_fringe_vtable;
    return this;
}
