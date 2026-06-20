// load_or_reuse_cached_x_mesh @ 0x405cc0 (thiscall, ret 4)

#include "cached_x_mesh_bank.h"
#include "object_render_types.h"

int strings_equal_case_insensitive_path(char* left, char* right);
void rstrcpy_checked_ascii(char* destination, char* source);

int CachedXMeshBank::load_or_reuse_cached_x_mesh(char* mesh_name)
{
    int i = 0;
    CachedXMeshSlot* slot;

    slot = slots;
    while (i < count) {
        if (strings_equal_case_insensitive_path(mesh_name, slot->name) != 0) {
            return i;
        }
        ++i;
        ++slot;
    }

    rstrcpy_checked_ascii(slots[count].name, mesh_name);
    slots[count].set_bod_object(g_object_list.add_object_to_list());
    load_x_mesh(mesh_name, slots[i].object, 1);

    ++count;
    return count - 1;
}
