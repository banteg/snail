// cRSubGolb::Explode(tVector) / spawn_golb_impact_sprite @ 0x415d80

#include "golb.h"
#include "player.h"
#include "runtime_config.h"
#include "sprite.h"

void GolbShot::spawn_golb_impact_sprite(Vector3* position)
{
    unsigned char render_flags = (unsigned char)g_runtime_config.render_flags;

    if ((render_flags & RUNTIME_RENDER_PARTICLE_EFFECTS) != 0) {
        int player_slot = owner_player->player_slot;
        cRSprite* impact_sprite = g_sprite_manager.New(player_slot, 0x21, -1, -1);
        int flags = impact_sprite->flags;
        flags |= SPRITE_FLAG_GAMEPLAY_OWNED;
        Vector3 impact_velocity;
        Vector3* sprite_velocity = &impact_sprite->velocity;
        impact_velocity.x = 0.0f;
        impact_velocity.y = 0.05f;
        impact_velocity.z = 0.0f;
        impact_sprite->flags = flags;
        impact_sprite->progress = 0.0f;
        impact_sprite->lifetime = 0.0f;
        impact_sprite->gravity_step = 0.0f;
        impact_sprite->progress_step = 0.055555552f;
        impact_sprite->lifetime_step = 0.83333337f;
        impact_sprite->size_start = 0.5f;
        impact_sprite->size_end = 1.0f;
        *sprite_velocity = impact_velocity;
        impact_sprite->position = *position;
    }
}
