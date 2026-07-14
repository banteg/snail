// allocate_sprite @ 0x44e2a0 (thiscall, ret 0x10)

#include "sprite.h"

Sprite* SpriteManager::allocate_sprite(int owner, int texture_id, int texture_a, int texture_b)
{
    int zero = 0;
    int primary_texture_id = texture_id;
    Sprite* sprite = free_head;
    if (sprite == 0) {
        return &g_sprite_sentinel;
    }

    free_head = sprite->next;
    sprite->owner = owner;

    Sprite* head = active_heads[owner];
    if (head != 0) {
        head->prev = sprite;
    }
    sprite->prev = 0;
    sprite->next = active_heads[owner];
    active_heads[owner] = sprite;

    sprite->initialize_sprite();

    sprite->flags |= 1 << (owner + RENDER_SCENE_BIT_BASE);
    sprite->texture_ref = g_sprite_texture_table[primary_texture_id];

    if (texture_b != -1) {
        sprite->flags |= 0x20;
        sprite->texture_ref_a = g_sprite_texture_table[texture_a];
        sprite->texture_ref_b = g_sprite_texture_table[texture_b];
    } else if (texture_a != -1) {
        sprite->flags |= 0x10;
        sprite->texture_ref_a = g_sprite_texture_table[texture_a];
    }

    sprite->size_end = 0.0f;
    sprite->texture_id = primary_texture_id;
    sprite->frame_progress = 0.0f;
    sprite->frame_progress_step = 0.0f;
    sprite->frame_count = g_sprite_texture_table[primary_texture_id]->frame_count;

    if ((g_sprite_texture_table[primary_texture_id]->flags
            & TEXTURE_REF_ANIMATED)
        != 0) {
        sprite->flags |= SPRITE_FLAG_ANIMATED;
        sprite->frame_progress_step = g_sprite_texture_table[primary_texture_id]->frame_progress_step;
        if ((g_sprite_texture_table[primary_texture_id]->flags
                & TEXTURE_REF_ANIMATION_PING_PONG)
            != 0) {
            sprite->flags |= SPRITE_FLAG_ANIMATION_PING_PONG;
        }
    }

    return sprite;
}
