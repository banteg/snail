// build_all_objects @ 0x42f9e0 (thiscall)

#include "object_render_types.h"

struct LoadingScreen {
    void update_loading_screen(); // @ 0x418e80
};

extern LoadingScreen g_loading_screen; // data_503290

void sort_object_faces_by_texture_group(Object* object); // @ 0x419fd0
void* build_object_texture_group_buffers(Object* object); // @ 0x413d50

void ObjectList::build_all_objects()
{
    int index = 0;
    if (count > 0) {
        int object_offset = 0;
        do {
            if ((index % 4) == 0) {
                g_loading_screen.update_loading_screen();
            }

            if (((Object*)((char*)objects + object_offset))->vertex_count != 0) {
                ((Object*)((char*)objects + object_offset))->calc_object_bounding_box();
                sort_object_faces_by_texture_group((Object*)((char*)objects + object_offset));
                ((Object*)((char*)objects + object_offset))->calc_object_texture_groups();

                if ((((Object*)((char*)objects + object_offset))->flags & 0x4000) != 0) {
                    ((Object*)((char*)objects + object_offset))->calc_object_facequad_normals();
                    ((Object*)((char*)objects + object_offset))->calc_object_edges();
                }

                build_object_texture_group_buffers((Object*)((char*)objects + object_offset));
            }

            ++index;
            object_offset += sizeof(Object);
        } while (index < count);
    }
}
