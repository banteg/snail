// register_sprite_texture @ 0x44e0f0 (stdcall, ret 0xc)

#include "sprite.h"

struct TextureRefList {
    TextureRef* get_or_create_texture_ref(char* texture_path, int arg3, short arg4);
};

extern TextureRefList g_texture_refs; // data_4b7790

void report_errorf(const char* format, ...);

TextureRef* __stdcall register_sprite_texture(char* texture_path, int texture_id, int flags)
{
    char* dot = texture_path;
    if (*texture_path != '.') {
        do {
            ++dot;
        } while (*dot != '.');
    }

    if (texture_id >= 1000) {
        report_errorf("Too many Sprite References - Increase RSPRITE_REFERENCE_MAX(%i) in RSprite.h", 1000);
    }

    TextureRef* texture = g_texture_refs.get_or_create_texture_ref(texture_path, 0, (short)flags);
    g_sprite_texture_table[texture_id] = texture;
    texture->flags |= flags;

    TextureRef* result = g_sprite_texture_table[texture_id];
    result->frame_count = 0;
    return result;
}
