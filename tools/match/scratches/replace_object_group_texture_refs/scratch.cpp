// replace_object_group_texture_refs @ 0x4145c0 (cdecl)

#include "object_render_types.h"
#include "sprite.h"

void replace_object_group_texture_refs(Object* object, TextureRef* new_texture,
    TextureRef* old_texture)
{
    if ((object->flags & OBJECT_FLAG_RENDER_BUFFERS_READY) == 0) {
        return;
    }

    int group = 0;
    if (object->texture_group_count <= 0) {
        return;
    }

    do {
        TextureRef** slot = object->group_texture_refs + group;
        TextureRef* texture = *slot;
        if (texture == old_texture) {
            *slot = new_texture;
        }
        ++group;
    } while (group < object->texture_group_count);
}
