// health_collect_particles @ 0x43a010 (thiscall, ret 0x4)

#include "player.h"
#include "sprite.h"
#include "track_health_pickup.h"

typedef unsigned int DWORD;

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
            char* sprite_bytes = (char*)sprite;
            DWORD* sprite_words = (DWORD*)sprite_bytes;

            sprite_words[1] |= 0x800u;
            sprite_words[26] = 0;
            sprite_words[27] = 0x3d2aaaab;
            sprite_words[30] = 0xb951b717;

            Color4f color;
            DWORD* color_words =
                (DWORD*)color.set_color_rgba(1.0f, 0.75f, 0.75f, 1.0f);
            float angle = (float)index * 0.785398185f;
            sprite_words[11] = color_words[0];
            float* position = (float*)(sprite_bytes + 0x48);
            sprite_words[12] = color_words[1];
            sprite_words[13] = color_words[2];
            DWORD alpha = color_words[3];
            sprite_words[24] = 0x3dcccccd;
            sprite_words[25] = 0x3f000000;
            sprite_words[14] = alpha;

            DWORD* source_position = (DWORD*)&pickup->sprite->position;
            float angle_for_sine = angle;
            ((DWORD*)position)[0] = source_position[0];
            ((DWORD*)position)[1] = source_position[1];
            ((DWORD*)position)[2] = source_position[2];

            float burst_velocity_z = velocity.z * 0.400000006f;
            float burst_velocity_y = cosine(angle) * 0.0149999997f;
            sprite_bytes += 0x54;
            float burst_velocity_x =
                sine(angle_for_sine) * 0.0149999997f;
            *(float*)sprite_bytes = burst_velocity_x;
            *((float*)sprite_bytes + 1) = burst_velocity_y;
            *((float*)sprite_bytes + 2) = burst_velocity_z;

            float offset_y = velocity.y * 3.0f;
            float offset_z = velocity.z * 3.0f;
            position[0] = velocity.x * 3.0f + position[0];
            position[1] = offset_y + position[1];
            ++index;
            position[2] = offset_z + position[2];
        } while (index < 8);
        result = index;
    }

    return result;
}
