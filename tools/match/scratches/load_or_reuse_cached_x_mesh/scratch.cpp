// load_or_reuse_cached_x_mesh @ 0x405cc0 (thiscall, ret 4)

#include "bod_types.h"
#include "object_render_types.h"

int strings_equal_case_insensitive_path(char* left, char* right);
void rstrcpy_checked_ascii(char* destination, char* source);

class CachedXMeshSlot : public BodBase {
public:
    char unknown_38[0x3c - 0x38];
    char name[0x80]; // +0x3c
};

typedef char CachedXMeshSlot_must_be_0xbc[(sizeof(CachedXMeshSlot) == 0xbc) ? 1 : -1];

class CachedXMeshBank {
public:
    void* unknown_00;
    int count;
    CachedXMeshSlot slots[1];

    int load_x_mesh(char* mesh_path, void* object, unsigned char options_flags);
    int load_or_reuse_cached_x_mesh(char* mesh_name);
};

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
