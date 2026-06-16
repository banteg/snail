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
        sprite->size_start = 0.30000001f;
        sprite->size_end = 1.3f;

        color.r = velocity->x * 0.2f;
        color.g = velocity->y * 0.2f;
        color.b = velocity->z * 0.2f;
        Vector3* out_velocity = &sprite->velocity;
        out_velocity->x = color.r;
        sprite->gravity_step = 0.0f;
        out_velocity->y = color.g;
        out_velocity->z = color.b;

        Vector3* out_position = &sprite->position;
        *out_position = *position;
    }
}
