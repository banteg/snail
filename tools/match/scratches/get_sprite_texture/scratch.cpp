// get_sprite_texture @ 0x44e570 (SpriteManager thiscall, ret 0x4)

#include "sprite.h"

TextureRef* SpriteManager::get_sprite_texture(int texture_id)
{
    return g_sprite_texture_table[texture_id];
}
