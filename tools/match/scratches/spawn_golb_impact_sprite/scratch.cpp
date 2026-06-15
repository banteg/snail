// spawn_golb_impact_sprite @ 0x415d80 (thiscall, ret 0x4)

#include "sprite.h"

struct Player {
    char unknown_000[0x380];
    int player_slot;       // +0x380
};

extern unsigned char g_render_effect_flags; // data_4df934

class GolbProjectile {
public:
    void spawn_golb_impact_sprite(Vector3* position);

    char unknown_000[0x278];
    Player* owner_player; // +0x278
};

void GolbProjectile::spawn_golb_impact_sprite(Vector3* position)
{
    unsigned char render_flags = g_render_effect_flags;

    if ((render_flags & 0x10) != 0) {
        Sprite* sprite = g_sprite_manager.allocate_sprite(owner_player->player_slot, 0x21, -1, -1);
        int flags = sprite->flags;
        flags |= 0x800;
        Vector3 velocity = { 0.0f, 0.05f, 0.0f };
        Vector3* out_velocity = &sprite->velocity;
        sprite->flags = flags;
        sprite->progress = 0.0f;
        sprite->lifetime = 0.0f;
        sprite->gravity_step = 0.0f;
        sprite->progress_step = 0.055555552f;
        sprite->lifetime_step = 0.83333337f;
        sprite->scale_x = 0.5f;
        sprite->scale_y = 1.0f;
        *out_velocity = velocity;
        sprite->position = *position;
    }
}
