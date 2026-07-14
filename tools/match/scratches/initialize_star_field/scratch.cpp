// initialize_star_field @ 0x434310 (thiscall)

#include "game_root.h"

extern GameRoot* g_game; // data_4df904

int next_math_random_value(); // @ 0x44c900

inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

inline Vector3 operator/(const Vector3& vector, float scale)
{
    return Vector3(vector.x / scale, vector.y / scale, vector.z / scale);
}

int StarManager::initialize_star_field()
{
    int i = 0;
    if (count > 0) {
        int offset = 0;
        do {
            *(Sprite**)((char*)entries + offset + 0x1c) =
                g_sprite_manager.allocate_sprite(2, 0x20, -1, -1);
            ++i;
            offset += sizeof(StarManagerEntry);
        } while (i < count);
    }

    int index = 0;
    fade = 1.0f;

    if (count > 0) {
        do {
            entries[index].active = 1;

            if (index == 0) {
                entries->alpha_scale = 0.400000006f;
            } else {
                entries[index].alpha_scale =
                    ((float)next_math_random_value() - 16384.0f) *
                        0.00000610351572f +
                    0.400000006f;
            }

            GameRoot* root = g_game;
            entries[index].position =
                root->overlay_0.transform.basis_forward * 50.0f +
                root->overlay_0.transform.position;

            entries[index].velocity = Vector3(
                ((float)next_math_random_value() - 16384.0f) * 0.0000610351562f,
                ((float)next_math_random_value() - 16384.0f) * 0.0000610351562f,
                0.0f);
            entries[index].velocity.normalize_vector();

            float velocity_scale =
                (float)next_math_random_value() * 0.0000183105476f + 0.300000012f;
            entries[index].velocity *= velocity_scale;
            entries[index].velocity.z = 0.0f;

            entries[index].speed = entries[index].velocity.vector_magnitude();
            entries[index].travel_distance =
                (float)next_math_random_value() * 0.00106811523f;

            entries[index].position =
                entries[index].velocity * entries[index].travel_distance /
                    entries[index].speed +
                entries[index].position;

            Sprite* sprite = entries[index].sprite;
            sprite->flags |= 0x402;
            entries[index].sprite->progress = 0.0f;
            entries[index].sprite->progress_step = 0.0f;
            entries[index].sprite->gravity_step = 0.0f;

            tColour color;
            entries[index].sprite->color =
                *color.set_color_rgba(0.800000012f, 0.800000012f, 1.0f, 0.400000006f);
            entries[index].sprite->size_start = 0.800000012f;
            entries[index].sprite->size_end = entries[index].sprite->size_start;
            entries[index].sprite->corner_scale =
                (entries[index].speed + 1.0f) * 4.0f;
            entries[index].sprite->velocity = entries[index].velocity;
            entries[index].sprite->position = entries[index].position;
            entries[index].sprite->facing_refresh_progress = 0.0f;

            ++index;
        } while (index < count);
    }

    return update_star_field_callback();
}
