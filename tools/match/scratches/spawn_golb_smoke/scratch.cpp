// spawn_golb_smoke @ 0x415c60 (thiscall, ret 0x4)

#include "golb.h"

void GolbProjectile::spawn_golb_smoke(Vector3* position)
{
    Sprite* sprite = g_sprite_manager.allocate_sprite(
        owner_player->player_slot,
        128,
        -1,
        -1);

    unsigned int flags = sprite->flags;
    sprite->progress = 0.0f;
    flags |= 0x800;
    sprite->flags = flags;

    float rate = game->subgame_rate;
    sprite->lifetime = 0.0f;
    sprite->progress_step = rate * 0.16666667f;
    sprite->lifetime_step = game->subgame_rate * 0.41666669f;

    Color4f color;
    sprite->color = *color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
    sprite->size_start = 0.1f;
    sprite->size_end = 0.5f;

    color.r = velocity.x * 0.40000001f;
    color.g = velocity.y * 0.40000001f;
    color.b = velocity.z * 0.40000001f;
    Vector3* out_velocity = &sprite->velocity;
    out_velocity->x = color.r;
    sprite->gravity_step = 0.0f;
    out_velocity->y = color.g;
    out_velocity->z = color.b;
    Vector3* out_position = &sprite->position;
    *out_position = *position;
}
