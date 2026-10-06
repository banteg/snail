// kill_game_sprites @ 0x44e3d0 (thiscall)

#include "sprite.h"

void cRSpriteManager::KillGame()
{
    cRSprite** bucket = g_sprite_active_heads;
    unsigned int game_sprite_flag = SPRITE_FLAG_GAMEPLAY_OWNED;

    do {
        cRSprite* sprite = *bucket;
        if (sprite != 0) {
            do {
                unsigned int flags = sprite->flags;
                cRSprite* next = sprite->next;
                if ((flags & game_sprite_flag) != 0) {
                    sprite->Kill();
                }
                sprite = next;
            } while (sprite != 0);
        }
        ++bucket;
    } while ((int)bucket < (int)&g_sprite_free_head);
}
