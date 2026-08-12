// health_collect_particles @ 0x43a010 (thiscall, ret 0x4)

#include "player.h"
#include "runtime_config.h"
#include "sprite.h"
#include "track_health_pickup.h"


float Sin(float radians);
float Cos(float radians);

void cRSubGoldy::HealthCollect(cRSubHealth* pickup)
{
    char render_flags = (char)g_runtime_config.render_flags;
    if ((render_flags & RUNTIME_RENDER_PARTICLE_EFFECTS) != 0) {
        int index = 0;
        do {
            // SpriteManager owns each ordinary burst sprite. The SubHealth
            // only lends its pickup sprite's current position.
            cRSprite* particle =
                g_sprite_manager.New(player_slot, 0x80, -1, -1);

            particle->flags |= SPRITE_FLAG_GAMEPLAY_OWNED;
            particle->progress = 0.0f;
            particle->progress_step = 0.041666668f;
            particle->gravity_step = -0.00019999999f;

            tColour color;
            particle->color = *color.Set(1.0f, 0.75f, 0.75f, 1.0f);
            Vector3* position = &particle->position;
            particle->size_start = 0.1f;
            particle->size_end = 0.5f;

            Vector3* pickup_sprite_position = &pickup->sprite->position;
            *position = *pickup_sprite_position;
            float angle = (float)index * 0.785398185f;

            Vector3 burst_velocity_value(
                Sin(angle) * 0.0149999997f,
                Cos(angle) * 0.0149999997f,
                velocity.z * 0.400000006f);
            particle->velocity = burst_velocity_value;

            Vector3 pickup_offset;
            pickup_offset.x = velocity.x * 3.0f;
            pickup_offset.y = velocity.y * 3.0f;
            pickup_offset.z = velocity.z * 3.0f;
            position->x = pickup_offset.x + position->x;
            position->y = pickup_offset.y + position->y;
            position->z = pickup_offset.z + position->z;
            ++index;
        } while (index < 8);
    }
}
