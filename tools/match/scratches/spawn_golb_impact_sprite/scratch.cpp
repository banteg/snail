// spawn_golb_impact_sprite @ 0x415d80 (thiscall, ret 0x4)

#include "golb.h"
#include "runtime_config.h"

void GolbShot::spawn_golb_impact_sprite(Vector3* position)
{
    unsigned char render_flags = (unsigned char)g_runtime_config.render_flags;

    if ((render_flags & 0x10) != 0) {
        int owner = owner_player->player_slot;
        Sprite* sprite = g_sprite_manager.allocate_sprite(owner, 0x21, -1, -1);
        int flags = sprite->flags;
        flags |= 0x800;
        Vector3 velocity;
        Vector3* out_velocity = &sprite->velocity;
        velocity.x = 0.0f;
        velocity.y = 0.05f;
        velocity.z = 0.0f;
        sprite->flags = flags;
        sprite->progress = 0.0f;
        sprite->lifetime = 0.0f;
        sprite->gravity_step = 0.0f;
        sprite->progress_step = 0.055555552f;
        sprite->lifetime_step = 0.83333337f;
        sprite->size_start = 0.5f;
        sprite->size_end = 1.0f;
        *out_velocity = velocity;
        sprite->position = *position;
    }
}
