// spawn_garbage_smoke_particle @ 0x43d5a0 (thiscall, ret 0xc)

#include "garbage_hazard_slot.h"
#include "player.h"
#include "runtime_config.h"
#include "subgame_runtime.h"


void cRSubGarbage::Smoke(
    tVector& position,
    tVector& velocity,
    cRSubGoldy* owner_player)
{
    char result = (char)g_runtime_config.render_flags;
    if ((result & 0x10) != 0) {
        cRSprite* sprite = g_sprite_manager.New(
            owner_player->player_slot,
            33,
            -1,
            -1);
        sprite->progress = 0.0f;
        sprite->flags |= SPRITE_FLAG_GAMEPLAY_OWNED;
        sprite->progress_step = owner_game->subgame_rate * 0.033333335f;
        sprite->lifetime = 0.0f;
        sprite->lifetime_step = owner_game->subgame_rate * 0.41666669f;

        {
            tColour color;
            sprite->color = *color.Set(1.0f, 1.0f, 1.0f, 1.0f);
        }
        float* sprite_words = (float*)sprite;
        sprite_words[24] = 0.30000001f;
        sprite_words[25] = 1.3f;

        tVector smoke_velocity = velocity * 0.2f;
        sprite->velocity = smoke_velocity;
        sprite->gravity_step = 0.0f;
        sprite->position = position;
    }
}
