// replace_object_list_texture_refs @ 0x430d90 (thiscall, ret 0x8)

#include "object_render_types.h"
#include "sprite.h"

void cRObjects::ReTextureObjects(cRTexture* new_texture,
    cRTexture* old_texture)
{
    int object_cursor = 0;
    int object_index = 0;
    if (count <= 0) {
        return;
    }

    int object_offset = 0;
    do {
        object_cursor += (int)objects;
        if (((Object*)object_cursor)->vertex_count != 0) {
            int face_index = 0;
            if (((Object*)object_cursor)->facequad_count > 0) {
                int face_offset = 0;
                do {
                    cRFaceQuad* quad = (cRFaceQuad*)((char*)((Object*)object_cursor)->facequads
                        + face_offset);
                    cRTexture** texture_slot = &quad->texture_ref;
                    if (*texture_slot == old_texture) {
                        *texture_slot = new_texture;
                    }
                    ++face_index;
                    face_offset += sizeof(cRFaceQuad);
                } while (face_index < ((Object*)object_cursor)->facequad_count);
            }

            replace_object_group_texture_refs(
                (Object*)object_cursor, new_texture, old_texture);
        }
        ++object_index;
        object_offset += sizeof(Object);
        object_cursor = object_offset;
    } while (object_index < count);
}
