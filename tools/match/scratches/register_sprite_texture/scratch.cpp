// register_sprite_texture @ 0x44e0f0 (SpriteManager thiscall, ret 0xc)

#include "sprite.h"

void report_errorf(const char* format, ...);

TextureRef* SpriteManager::register_sprite_texture(char* texture_path, int texture_id, int flags)
{
    char* dot = texture_path;
    if (*texture_path != '.') {
        do {
            ++dot;
        } while (*dot != '.');
    }

    if (texture_id >= SPRITE_TEXTURE_CAPACITY) {
        report_errorf("Too many Sprite References - Increase RSPRITE_REFERENCE_MAX(%i) in RSprite.h", SPRITE_TEXTURE_CAPACITY);
    }

    TextureRef* texture = g_texture_refs.get_or_create_texture_ref(texture_path, 0, flags);
    g_sprite_texture_table[texture_id] = texture;
    texture->flags |= flags;

    TextureRef* result = g_sprite_texture_table[texture_id];
    result->frame_count = 0;
    return result;
}
