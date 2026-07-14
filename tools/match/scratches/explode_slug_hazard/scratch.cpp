// explode_slug_hazard @ 0x43f680 (thiscall, ret)

#include "slug_hazard_types.h"
#include "sprite.h"
#include "subgame_runtime.h"

int next_math_random_value();

void Slug::explode_slug_hazard()
{
    int count = 70;
    do {
        float spread = (float)next_math_random_value() * 0.0000061035157f + 0.2f;
        float size = (float)next_math_random_value() * 0.000030517578f;
        size = size * 0.75f + 0.25f;
        Sprite* sprite = g_sprite_manager.allocate_sprite(1, 129, -1, -1);
        sprite->progress = 0.0f;
        sprite->flags |=
            SPRITE_FLAG_GAMEPLAY_OWNED | SPRITE_FLAG_ORIENT_TO_MOTION;
        sprite->corner_scale = size + size;
        float progress_step =
            1.0f
            / (((float)next_math_random_value() * 0.000015258789f + 0.60000002f) * 60.0f)
            * owner_game->subgame_rate;
        sprite->lifetime = 0.0f;
        sprite->lifetime_step = 0.0f;
        sprite->progress_step = progress_step;
        sprite->color.set_color_grayscale(
            (float)next_math_random_value() * 0.0000091552738f
            + 0.69999999f);
        sprite->size_start = size * 0.30000001f;
        sprite->size_end = size * 1.2f;
        float rate = owner_game->subgame_rate;
        float gravity_step = rate * rate;
        gravity_step *= -0.0099999998f;
        sprite->gravity_step = gravity_step * 2.2f;

        Vector3 random_velocity;
        random_velocity.x =
            ((float)next_math_random_value() - 16384.0f) * spread * 0.000061035156f;
        random_velocity.y =
            (float)next_math_random_value() * (spread + 0.30000001f) * 0.000030517578f;
        SubgameRuntime* game = owner_game;
        random_velocity.z =
            (float)next_math_random_value() * spread * 0.000030517578f
            + game->player.velocity.z;
        float speed = game->subgame_rate;
        sprite->velocity = random_velocity * speed;

        Vector3* velocity = &sprite->velocity;
        float position_scale = (float)next_math_random_value() * 0.00030517578f;
        Vector3 position_offset;
        position_offset.x = position_scale * velocity->x;
        position_offset.y = position_scale * velocity->y;
        position_offset.z = position_scale * velocity->z;
        Vector3 staged_position;
        staged_position.x = position_offset.x + transform.position.x;
        staged_position.y = position_offset.y + transform.position.y;
        staged_position.z = position_offset.z + transform.position.z;
        sprite->position = staged_position;
    } while (--count);
}
