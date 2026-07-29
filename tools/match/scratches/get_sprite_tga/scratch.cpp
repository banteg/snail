// get_sprite_tga @ 0x44e580 (cRSpriteManager thiscall, ret 0x4)

#include "sprite.h"
#include "tga_image_view.h"

TgaImageView* cRSpriteManager::get_sprite_tga(int texture_id)
{
    return (TgaImageView*)g_sprite_texture_table[texture_id]->texture_ref;
}
