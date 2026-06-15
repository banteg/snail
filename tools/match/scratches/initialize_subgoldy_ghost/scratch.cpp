// initialize_subgoldy_ghost @ 0x43d230 (thiscall, ret 0x4)

#include "sprite.h"

class Player {
public:
    int initialize_subgoldy_ghost(int owner);

    char unknown_00[0x98];
    Sprite* ghost_sprite_a;
    Sprite* ghost_sprite_b;
};

int Player::initialize_subgoldy_ghost(int owner)
{
    Color4f color;

    ghost_sprite_a = g_sprite_manager.allocate_sprite(owner, 159, -1, -1);
    ghost_sprite_a->flags |= 0x800;
    ghost_sprite_a->progress = 0.0f;
    ghost_sprite_a->progress_step = 0.0f;
    ghost_sprite_a->gravity_step = 0.0f;
    ghost_sprite_a->color = *color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
    ghost_sprite_a->scale_x = 0.5f;
    ghost_sprite_a->scale_y = 0.5f;
    ghost_sprite_a->position.x = 4.5f;
    ghost_sprite_a->position.y = 1.0f;
    ghost_sprite_a->position.z = 0.0f;

    ghost_sprite_b = g_sprite_manager.allocate_sprite(owner, 159, -1, -1);
    ghost_sprite_b->flags |= 0x800;
    ghost_sprite_b->progress = 0.0f;
    ghost_sprite_b->progress_step = 0.0f;
    ghost_sprite_b->gravity_step = 0.0f;
    ghost_sprite_b->color = *color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
    ghost_sprite_b->scale_x = 0.5f;
    ghost_sprite_b->scale_y = 0.5f;
    ghost_sprite_b->position.x = -4.5f;
    ghost_sprite_b->position.y = 1.0f;
    ghost_sprite_b->position.z = 0.0f;

    int clear_visible_mask = ~0x40;
    Sprite* first_ghost = ghost_sprite_a;
    first_ghost->flags &= clear_visible_mask;

    Sprite* second_ghost = ghost_sprite_b;
    return second_ghost->flags &= clear_visible_mask;
}
