// calc_object_texture_groups @ 0x4303f0 (thiscall)

#include "object_render_types.h"
#include "sprite.h"

void Object::calc_object_texture_groups()
{
    for (int pass = 0; pass < 2; ++pass) {
        ObjectFaceQuad* quads = facequads;
        int group = 0;
        int face_index = 0;
        TextureRef* texture = quads[0].texture_ref;

        if (facequad_count > 0) {
            int offset = 0;
            do {
                ObjectFaceQuad* quad = (ObjectFaceQuad*)((char*)quads + offset);

                if ((flags & 0x400) != 0) {
                    quad->flags |= 2;
                    quad->texture_ref->flags |= 0x20;
                }

                if (quad->texture_ref != texture || (quad->flags & 0x10) != 0) {
                    if (pass == 1) {
                        texture_group_ends[group] = face_index;
                    }
                    ++group;
                    texture = quad->texture_ref;
                }

                ++face_index;
                offset += 0x30;
            } while (face_index < facequad_count);
        }

        if (pass == 1) {
            texture_group_ends[group] = face_index;
        } else if (pass == 0) {
            request_object_texture_groups(group + 1);
        }
    }
}
