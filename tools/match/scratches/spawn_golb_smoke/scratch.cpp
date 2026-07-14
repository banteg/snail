// spawn_golb_smoke @ 0x415c60 (thiscall, ret 0x4)

#include "golb.h"
#include "subgame_runtime.h"

void GolbShot::spawn_golb_smoke(Vector3* position)
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

    tColour color;
    sprite->color = *color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
    float* sprite_words = (float*)sprite;
    sprite_words[24] = 0.1f;
    sprite_words[25] = 0.5f;

    float* out_velocity = sprite_words + 21;
    float* out_position = sprite_words + 18;
    color.r = velocity.x * 0.40000001f;
    color.g = velocity.y * 0.40000001f;
    color.b = velocity.z * 0.40000001f;
    *out_velocity = color.r;
    out_position[12] = 0.0f;
    out_velocity[1] = color.g;
    out_velocity[2] = color.b;
    *out_position = position->x;
    out_position[1] = position->y;
    out_position[2] = position->z;
}
