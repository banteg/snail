// replace_object_list_texture_refs @ 0x430d90 (thiscall, ret 0x8)

#include "object_render_types.h"
#include "sprite.h"

void ObjectList::replace_object_list_texture_refs(TextureRef* new_texture,
    TextureRef* old_texture)
{
    int object_index = 0;
    int object_offset = 0;
    if (count <= 0) {
        return;
    }

    do {
        Object* object = (Object*)((char*)objects + object_offset);
        if (object->vertex_count != 0) {
            int face_index = 0;
            if (object->facequad_count > 0) {
                int face_offset = 0;
                do {
                    ObjectFaceQuad* quad =
                        (ObjectFaceQuad*)((char*)object->facequads + face_offset);
                    if (quad->texture_ref == old_texture) {
                        quad->texture_ref = new_texture;
                    }
                    ++face_index;
                    face_offset += 0x30;
                } while (face_index < object->facequad_count);
            }

            replace_object_group_texture_refs(object, new_texture, old_texture);
        }
        ++object_index;
        object_offset += 0xdc;
    } while (object_index < count);
}
