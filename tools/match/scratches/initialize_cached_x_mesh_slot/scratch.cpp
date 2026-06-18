// initialize_cached_x_mesh_slot @ 0x408470 (thiscall, ret)

#include "bod_types.h"

extern void* g_cached_x_mesh_slot_vtable; // off_49730c / data_49730c

class CachedXMeshSlot : public BodBase {
public:
    CachedXMeshSlot* initialize_cached_x_mesh_slot();

    char unknown_038[0xbc - 0x038];
};

CachedXMeshSlot* CachedXMeshSlot::initialize_cached_x_mesh_slot()
{
    initialize_bod_base();
    vtable = &g_cached_x_mesh_slot_vtable;
    return this;
}
