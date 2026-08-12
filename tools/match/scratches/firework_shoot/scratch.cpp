// firework_shoot @ 0x441dd0 (thiscall, ret 0x10)

#include "firework.h"
#include "rmath_random.h"
#include "runtime_config.h"
#include "sprite.h"


int next_math_random_value();

void cRFireWork::firework_shoot(
    Vector3* position, int owner, int texture_id, int count)
{
    if ((g_runtime_config.render_flags & RUNTIME_RENDER_PARTICLE_EFFECTS) == 0
        || count <= 0)
        return;

    int remaining = count;
    do {
        cRSprite* sprite = g_sprite_manager.New(owner, texture_id, -1, -1);
        sprite->draw_mode = 10;
        sprite->flags |=
            SPRITE_FLAG_GAMEPLAY_OWNED | SPRITE_FLAG_ORIENT_TO_MOTION;
        sprite->corner_scale = 4.0f;
        sprite->progress = 0.0f;

        float duration = (float)random_float_below(0.5f, 0) + 0.800000012f;
        sprite->lifetime = 0.0f;
        sprite->lifetime_step = 0.277777791f;
        sprite->progress_step = 1.0f / (duration * 60.0f);

        float red = (float)random_float_below(0.300000012f, 0) + 0.699999988f;
        sprite->color.Set(red, red * 0.5f, 0.0f);

        sprite->size_start = 0.5f;
        sprite->size_end = 0.100000001f;

        Vector3 velocity(
            ((float)next_math_random_value() - 16384.0f)
                * 0.0000610351562f * 0.2f,
            ((float)next_math_random_value() - 16384.0f)
                    * 0.0000610351562f * 0.3f
                + 0.100000001f,
            ((float)next_math_random_value() - 16384.0f)
                * 0.0000610351562f * 0.2f);

        sprite->depth_offset = 0.0f;
        sprite->velocity = velocity;
        Vector3* out_position = &sprite->position;
        *out_position = *position;
    } while (--remaining != 0);
}
