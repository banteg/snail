// firework_shoot @ 0x441dd0 (thiscall, ret 0x10)

#include "firework.h"
#include "runtime_config.h"
#include "sprite.h"


double random_float_below(float upper_bound, int tag);
int next_math_random_value();

void FireWork::firework_shoot(
    Vector3* position, int owner, int texture_id, int count)
{
    if ((g_runtime_config.render_flags & RUNTIME_RENDER_PARTICLE_EFFECTS) == 0
        || count <= 0)
        return;

    int remaining = count;
    Vector3 velocity;

    do {
        Sprite* sprite = g_sprite_manager.allocate_sprite(owner, texture_id, -1, -1);
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
        sprite->color.set_color_rgb(red, red * 0.5f, 0.0f);

        sprite->size_start = 0.5f;
        sprite->size_end = 0.100000001f;

        float velocity_z =
            ((float)next_math_random_value() - 16384.0f) * 0.0000122070314f;
        float velocity_y =
            ((float)next_math_random_value() - 16384.0f) * 0.0000183105476f
            + 0.100000001f;
        velocity.x =
            ((float)next_math_random_value() - 16384.0f) * 0.0000122070314f;
        velocity.y = velocity_y;
        velocity.z = velocity_z;

        sprite->depth_offset = 0.0f;
        sprite->velocity = velocity;
        Vector3* out_position = &sprite->position;
        *out_position = *position;
    } while (--remaining != 0);
}
