// initialize_subgoldy_ghost @ 0x43d230 (thiscall, ret 0x4)

#include "sprite.h"
#include "player.h"

void Player::initialize_subgoldy_ghost(int owner)
{
    tColour color;

    ghost_sprite_a = g_sprite_manager.allocate_sprite(owner, 159, -1, -1);
    ghost_sprite_a->flags |= SPRITE_FLAG_GAMEPLAY_OWNED;
    ghost_sprite_a->progress = 0.0f;
    ghost_sprite_a->progress_step = 0.0f;
    ghost_sprite_a->gravity_step = 0.0f;
    ghost_sprite_a->color = *color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
    ghost_sprite_a->size_start = 0.5f;
    ghost_sprite_a->size_end = 0.5f;
    ghost_sprite_a->position.x = 4.5f;
    ghost_sprite_a->position.y = 1.0f;
    ghost_sprite_a->position.z = 0.0f;

    ghost_sprite_b = g_sprite_manager.allocate_sprite(owner, 159, -1, -1);
    ghost_sprite_b->flags |= SPRITE_FLAG_GAMEPLAY_OWNED;
    ghost_sprite_b->progress = 0.0f;
    ghost_sprite_b->progress_step = 0.0f;
    ghost_sprite_b->gravity_step = 0.0f;
    ghost_sprite_b->color = *color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
    ghost_sprite_b->size_start = 0.5f;
    ghost_sprite_b->size_end = 0.5f;
    ghost_sprite_b->position.x = -4.5f;
    ghost_sprite_b->position.y = 1.0f;
    ghost_sprite_b->position.z = 0.0f;

    int clear_visible_mask = ~SPRITE_FLAG_RENDER_ENABLED;
    Sprite* first_ghost = ghost_sprite_a;
    first_ghost->flags &= clear_visible_mask;

    Sprite* second_ghost = ghost_sprite_b;
    second_ghost->flags &= clear_visible_mask;
}
