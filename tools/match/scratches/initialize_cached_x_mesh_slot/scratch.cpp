// initialize_cached_x_mesh_slot @ 0x408470 (thiscall, ret)

#include "cached_x_mesh_bank.h"

extern void* g_cached_x_mesh_slot_vtable; // off_49730c / data_49730c

CachedXMeshSlot* CachedXMeshSlot::initialize_cached_x_mesh_slot()
{
    initialize_bod_base();
    vtable = &g_cached_x_mesh_slot_vtable;
    return this;
}
