// CalcTextureGroups @ 0x4303f0 (thiscall)

#include "object_render_types.h"
#include "sprite.h"

void cRObject::CalcTextureGroups()
{
    int pass = 0;
    do {
        char* quads = (char*)facequads;
        int group = 0;
        int face_index = 0;
        cRTexture* texture = *(cRTexture**)(quads + 0x0c);

        if (facequad_count > 0) {
            int offset = 0;
            do {
                if ((flags & 0x400) != 0) {
                    quads[offset] |= 2;
                    cRTexture* active_texture =
                        *(cRTexture**)((char*)facequads + offset + 0x0c);
                    active_texture->flags |= TEXTURE_REF_RETAIN_SOURCE_BYTES;
                }

                quads = (char*)facequads;
                if (*(cRTexture**)(quads + offset + 0x0c) != texture
                    || (quads[offset] & 0x10) != 0) {
                    if (pass == 1) {
                        texture_group_ends[group] = face_index;
                    }
                    ++group;
                    quads = (char*)facequads;
                    texture = *(cRTexture**)(quads + offset + 0x0c);
                }

                ++face_index;
                offset += 0x30;
            } while (face_index < facequad_count);
        }

        if (pass == 1) {
            texture_group_ends[group] = face_index;
        } else if (pass == 0) {
            RequestFaceQuadTextureGroups(group + 1);
        }
        ++pass;
    } while (pass < 2);
}
