// health_collect_particles @ 0x43a010 (thiscall, ret 0x4)

#include "player.h"
#include "sprite.h"
#include "track_health_pickup.h"

extern unsigned char g_render_flags; // byte_4df934

float sine(float radians);
float cosine(float radians);

char Player::health_collect_particles(TrackHealthPickup* pickup)
{
    char result = g_render_flags;
    if ((result & 0x10) != 0) {
        int index = 0;
        do {
            Sprite* sprite =
                g_sprite_manager.allocate_sprite(player_slot, 0x80, -1, -1);

            sprite->flags |= 0x800u;
            sprite->progress = 0.0f;
            sprite->progress_step = 0.041666668f;
            sprite->gravity_step = -0.00019999999f;

            Color4f color;
            sprite->color = *color.set_color_rgba(1.0f, 0.75f, 0.75f, 1.0f);
            float angle = (float)index * 0.785398185f;
            Vector3* position = &sprite->position;
            sprite->size_start = 0.1f;
            sprite->size_end = 0.5f;

            Vector3* source_position = &pickup->sprite->position;
            float angle_for_sine = angle;
            *position = *source_position;

            float burst_velocity_z = velocity.z * 0.400000006f;
            float burst_velocity_y = cosine(angle) * 0.0149999997f;
            Vector3* burst_velocity = &sprite->velocity;
            float burst_velocity_x =
                sine(angle_for_sine) * 0.0149999997f;
            burst_velocity->x = burst_velocity_x;
            burst_velocity->y = burst_velocity_y;
            burst_velocity->z = burst_velocity_z;

            float offset_y = velocity.y * 3.0f;
            float offset_z = velocity.z * 3.0f;
            position->x = velocity.x * 3.0f + position->x;
            position->y = offset_y + position->y;
            ++index;
            position->z = offset_z + position->z;
        } while (index < 8);
        result = index;
    }

    return result;
}
