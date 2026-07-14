// kill_game_sprites @ 0x44e3d0 (thiscall)

#include "sprite.h"

void SpriteManager::kill_game_sprites()
{
    Sprite** bucket = g_sprite_active_heads;
    unsigned int game_sprite_flag = SPRITE_FLAG_GAMEPLAY_OWNED;

    do {
        Sprite* sprite = *bucket;
        if (sprite != 0) {
            do {
                unsigned int flags = sprite->flags;
                Sprite* next = sprite->next;
                if ((flags & game_sprite_flag) != 0) {
                    sprite->kill_sprite();
                }
                sprite = next;
            } while (sprite != 0);
        }
        ++bucket;
    } while ((int)bucket < (int)&g_sprite_free_head);
}
