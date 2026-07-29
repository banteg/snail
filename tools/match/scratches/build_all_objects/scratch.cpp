// build_all_objects @ 0x42f9e0 (thiscall)

#include "loading_bar.h"
#include "object_render_types.h"

void cRObjects::build_all_objects()
{
    int index = 0;
    if (count > 0) {
        int object_offset = 0;
        do {
            if ((index % 4) == 0) {
                g_loading_bar.update_loading_screen();
            }

            if (((Object*)((char*)objects + object_offset))->vertex_count != 0) {
                ((Object*)((char*)objects + object_offset))->calc_object_bounding_box();
                sort_object_faces_by_texture_group((Object*)((char*)objects + object_offset));
                ((Object*)((char*)objects + object_offset))->CalcTextureGroups();

                if ((((Object*)((char*)objects + object_offset))->flags
                        & OBJECT_FLAG_TOON_ENABLED) != 0) {
                    ((Object*)((char*)objects + object_offset))->CalcFaceQuadNormals();
                    ((Object*)((char*)objects + object_offset))->CalcEdges();
                }

                build_object_texture_group_buffers((Object*)((char*)objects + object_offset));
            }

            ++index;
            object_offset += sizeof(Object);
        } while (index < count);
    }
}
