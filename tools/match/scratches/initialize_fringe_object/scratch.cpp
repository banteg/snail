// initialize_fringe_object @ 0x408650 (thiscall, ret)
// Authored owner: cRFringe::cRFringe().

#include "fringe_object.h"

extern void* g_fringe_vtable; // off_497344 / data_497344

cRFringe::cRFringe()
{
    vtable = &g_fringe_vtable;
}
