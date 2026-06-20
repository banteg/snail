// health_collect_particles @ 0x43a010 (thiscall, ret 0x4)

#include "player.h"
#include "sprite.h"
#include "track_health_pickup.h"

extern unsigned char g_render_flags; // byte_4df934

float sine(float radians);
float cosine(float radians);

void Player::health_collect_particles(TrackHealthPickup* pickup)
{
    char render_flags = g_render_flags;
    if ((render_flags & 0x10) != 0) {
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
            Vector3* position = &sprite->position;
            sprite->size_start = 0.1f;
            sprite->size_end = 0.5f;

            Vector3* source_position = &pickup->sprite->position;
            *position = *source_position;
            float angle = (float)index * 0.785398185f;

            Vector3 burst_velocity_value(
                sine(angle) * 0.0149999997f,
                cosine(angle) * 0.0149999997f,
                velocity.z * 0.400000006f);
            sprite->velocity = burst_velocity_value;

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
