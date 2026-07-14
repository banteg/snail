// get_sprite_texture_ref @ 0x44e580 (SpriteManager thiscall, ret 0x4)

#include "sprite.h"
#include "tga_image_view.h"

TgaImageView* SpriteManager::get_sprite_tga(int texture_id)
{
    return (TgaImageView*)g_sprite_texture_table[texture_id]->texture_ref;
}
