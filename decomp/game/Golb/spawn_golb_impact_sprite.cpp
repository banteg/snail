// cRSubGolb::Explode(tVector*) @ 0x415d80

#include "golb.h"
#include "player.h"
#include "runtime_config.h"
#include "sprite.h"

void cRSubGolb::Explode(Vector3* position)
{
    unsigned char render_flags = (unsigned char)g_runtime_config.render_flags;

    if ((render_flags & RUNTIME_RENDER_PARTICLE_EFFECTS) != 0) {
        cRSprite* impact_sprite = g_sprite_manager.New(owner_player->player_slot, 0x21, -1, -1);
        int flags = impact_sprite->flags;
        flags |= SPRITE_FLAG_GAMEPLAY_OWNED;
        impact_sprite->flags = flags;
        impact_sprite->progress = 0.0f;
        impact_sprite->lifetime = 0.0f;
        impact_sprite->velocity = Vector3(0.0f, 0.05f, 0.0f);
        impact_sprite->gravity_step = 0.0f;
        impact_sprite->progress_step = 0.055555552f;
        impact_sprite->lifetime_step = 0.83333337f;
        impact_sprite->size_start = 0.5f;
        impact_sprite->size_end = 1.0f;
        impact_sprite->position = *position;
    }
}
