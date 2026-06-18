// initialize_star_field @ 0x434310 (thiscall)

#include "star_field.h"

extern char* g_game_base; // data_4df904

int next_math_random_value(); // @ 0x44c900

int StarField::initialize_star_field()
{
    int i = 0;
    if (count > 0) {
        int offset = 0;
        do {
            *(Sprite**)((char*)entries + offset + 0x1c) =
                g_sprite_manager.allocate_sprite(2, 0x20, -1, -1);
            ++i;
            offset += sizeof(StarFieldEntry);
        } while (i < count);
    }

    int zero = 0;
    int index = 0;
    fade = 1.0f;

    if (count > 0) {
        do {
            StarFieldEntry* entry = &entries[index];
            entry->active = 1;

            if (index != 0) {
                entry->twinkle_scale =
                    ((float)next_math_random_value() - 16384.0f) *
                        0.00000610351572f +
                    0.400000006f;
            } else {
                entries->twinkle_scale = 0.400000006f;
            }

            char* game = g_game_base;
            entry->position.x =
                *(float*)(game + 0x6d4) * 50.0f + *(float*)(game + 0x6e4);
            entry->position.y =
                *(float*)(game + 0x6d8) * 50.0f + *(float*)(game + 0x6e8);
            entry->position.z =
                *(float*)(game + 0x6dc) * 50.0f + *(float*)(game + 0x6ec);

            float velocity_y =
                ((float)next_math_random_value() - 16384.0f) * 0.0000610351562f;
            entry->velocity.x =
                ((float)next_math_random_value() - 16384.0f) * 0.0000610351562f;
            entry->velocity.y = velocity_y;
            entry->velocity.z = 0.0f;
            entry->velocity.normalize_vector();

            float velocity_scale =
                (float)next_math_random_value() * 0.0000183105476f + 0.300000012f;
            entry->velocity.x = velocity_scale * entry->velocity.x;
            entry->velocity.y = velocity_scale * entry->velocity.y;
            entry->velocity.z = velocity_scale * entry->velocity.z;
            entry->velocity.z = 0.0f;

            entry->speed = entry->velocity.vector_magnitude();
            entry->phase = (float)next_math_random_value() * 0.00106811523f;

            entry->position.x =
                (entry->phase * entry->velocity.x) / entry->speed + entry->position.x;
            entry->position.y =
                (entry->phase * entry->velocity.y) / entry->speed + entry->position.y;
            entry->position.z =
                (entry->phase * entry->velocity.z) / entry->speed + entry->position.z;

            Sprite* sprite = entry->sprite;
            sprite->flags |= 0x402;
            entry->sprite->progress = 0.0f;
            entry->sprite->progress_step = 0.0f;
            entry->sprite->gravity_step = 0.0f;

            Color4f color;
            entry->sprite->color =
                *color.set_color_rgba(0.800000012f, 0.800000012f, 1.0f, 0.400000006f);
            entry->sprite->size_start = 0.800000012f;
            entry->sprite->size_end = entry->sprite->size_start;
            entry->sprite->corner_scale = (entry->speed + 1.0f) * 4.0f;
            entry->sprite->velocity = entry->velocity;
            entry->sprite->position = entry->position;
            entry->sprite->facing_refresh_progress = (float)zero;

            ++index;
        } while (index < count);
    }

    return update_star_field_callback();
}
