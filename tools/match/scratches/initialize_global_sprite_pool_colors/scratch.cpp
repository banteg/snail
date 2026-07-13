// initialize_global_sprite_pool_colors @ 0x44de50 (cdecl)

#include "sprite.h"

void initialize_global_sprite_pool_colors()
{
    Sprite* sprite = g_sprite_manager.sprites;
    for (int count = SPRITE_POOL_CAPACITY; count != 0; --count) {
        sprite->color.noop_this_constructor();
        ++sprite;
    }
}
