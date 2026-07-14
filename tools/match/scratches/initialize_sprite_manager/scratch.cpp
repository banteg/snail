// initialize_sprite_manager @ 0x44e160 (thiscall)

#include "sprite.h"

void SpriteManager::initialize_sprite_manager()
{
    paused = 0;
    for (int bucket = 0; bucket < SPRITE_ACTIVE_LIST_COUNT; ++bucket) {
        active_heads[bucket] = 0;
    }
    free_head = &sprites[0];

    int index = 0;
    do {
        sprites[index].initialize_sprite();

        if (index == 0) {
            sprites[index].prev = 0;
            sprites[index].next = &sprites[index + 1];
        } else if (index == SPRITE_POOL_CAPACITY - 1) {
            sprites[index].prev = &sprites[index - 1];
            sprites[index].next = 0;
        } else {
            sprites[index].prev = &sprites[index - 1];
            sprites[index].next = &sprites[index + 1];
        }
        ++index;
    } while (index < SPRITE_POOL_CAPACITY);
}
