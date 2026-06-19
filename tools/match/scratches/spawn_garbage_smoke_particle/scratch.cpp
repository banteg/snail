// spawn_garbage_smoke_particle @ 0x43d5a0 (thiscall, ret 0xc)

#include "garbage_hazard_slot.h"
#include "player.h"

class Game {
public:
    char unknown_00[0x38];
    float subgame_rate; // +0x38
};

extern unsigned char g_render_flags; // byte_4df934

void GarbageHazardSlot::spawn_garbage_smoke_particle(
    Vector3* position,
    Vector3* velocity,
    Player* player)
{
    char result = g_render_flags;
    if ((result & 0x10) != 0) {
        Sprite* sprite = g_sprite_manager.allocate_sprite(
            player->player_slot,
            33,
            -1,
            -1);
        sprite->progress = 0.0f;
        sprite->flags |= 0x800;
        sprite->progress_step = game->subgame_rate * 0.033333335f;
        sprite->lifetime = 0.0f;
        sprite->lifetime_step = game->subgame_rate * 0.41666669f;

        Color4f color;
        sprite->color = *color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
        float* sprite_words = (float*)sprite;
        sprite_words[24] = 0.30000001f;
        sprite_words[25] = 1.3f;

        float* out_velocity = sprite_words + 21;
        float* out_position = sprite_words + 18;
        color.r = velocity->x * 0.2f;
        color.g = velocity->y * 0.2f;
        color.b = velocity->z * 0.2f;
        *out_velocity = color.r;
        out_position[12] = 0.0f;
        out_velocity[1] = color.g;
        out_velocity[2] = color.b;

        *out_position = position->x;
        out_position[1] = position->y;
        out_position[2] = position->z;
    }
}
