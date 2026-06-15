// set_sprite_texture_ref @ 0x44e550 (thiscall, ret 0x8)

#include "sprite.h"

TextureRef* Sprite::set_sprite_texture_ref(int texture_id, int frame)
{
    TextureRef* ref = g_sprite_texture_table[texture_id] + frame;
    texture_ref = ref;
    return ref;
}
