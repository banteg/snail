// initialize_active_landscape_entry @ 0x408820 (thiscall, ret)

#include "active_landscape_entry.h"

extern void* g_active_landscape_entry_vtable; // off_497360 / data_497360

ActiveLandscapeEntry* ActiveLandscapeEntry::initialize_active_landscape_entry()
{
    initialize_renderable_bod();
    vtable = &g_active_landscape_entry_vtable;
    return this;
}
