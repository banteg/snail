// load_or_reuse_cached_x_mesh @ 0x405cc0 (thiscall, ret 4)

#include "directx_loader.h"
#include "object_render_types.h"

int strings_equal_case_insensitive_path(char* left, char* right);
void rstrcpy_checked_ascii(char* destination, char* source);

int DirectXLoader::load_or_reuse_cached_x_mesh(char* mesh_name)
{
    int i = 0;
    CachedXMeshSlot* slot;

    slot = cached_x_mesh_slots;
    while (i < cached_x_mesh_count) {
        if (strings_equal_case_insensitive_path(mesh_name, slot->name) != 0) {
            return i;
        }
        ++i;
        ++slot;
    }

    rstrcpy_checked_ascii(cached_x_mesh_slots[cached_x_mesh_count].name, mesh_name);
    cached_x_mesh_slots[cached_x_mesh_count].set_bod_object(g_object_list.add_object_to_list());
    load_x_mesh(mesh_name, cached_x_mesh_slots[i].object, 1);

    ++cached_x_mesh_count;
    return cached_x_mesh_count - 1;
}
