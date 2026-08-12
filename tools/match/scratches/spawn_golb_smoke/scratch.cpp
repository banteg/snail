// cRSubGolb::Smoke(tVector) / spawn_golb_smoke @ 0x415c60

#include "golb.h"
#include "sprite.h"
#include "subgame_runtime.h"

void cRSubGolb::spawn_golb_smoke(Vector3* position)
{
    cRSprite* sprite = g_sprite_manager.New(
        owner_player->player_slot,
        128,
        -1,
        -1);

    unsigned int flags = sprite->flags;
    sprite->progress = 0.0f;
    flags |= SPRITE_FLAG_GAMEPLAY_OWNED;
    sprite->flags = flags;

    float rate = game->subgame_rate;
    sprite->lifetime = 0.0f;
    sprite->progress_step = rate * 0.16666667f;
    sprite->lifetime_step = game->subgame_rate * 0.41666669f;

    {
        tColour color;
        sprite->color = *color.Set(1.0f, 1.0f, 1.0f, 1.0f);
    }
    float* sprite_words = (float*)sprite;
    sprite_words[24] = 0.1f;
    sprite_words[25] = 0.5f;

    Vector3 smoke_velocity = velocity * 0.40000001f;
    sprite->velocity = smoke_velocity;
    sprite->gravity_step = 0.0f;
    sprite->position = *position;
}
