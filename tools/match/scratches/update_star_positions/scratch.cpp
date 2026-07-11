// update_star_positions @ 0x434800 (thiscall, ret 0x4)

#include "game_root.h"
#include "star_field.h"

extern char* g_game_base; // data_4df904

void* StarField::update_star_positions(float fade_alpha)
{
    void* result = (void*)count;
    int i = 0;
    if (count > 0) {
        do {
            StarFieldEntry* entry = &entries[i];
            entry->travel_distance = entry->speed + entry->travel_distance;
            if (entry->travel_distance > 35.0f) {
                float* travel_distance = &entry->travel_distance;
                *travel_distance = 0.0f;
                entry->sprite->facing_refresh_progress = 0.0f;

                GameRoot* game = (GameRoot*)g_game_base;
                Vector3 direction_scaled;
                Vector3 staged_position;
                direction_scaled.x = game->overlay_0.transform.basis_forward.x * 50.0f;
                direction_scaled.y = game->overlay_0.transform.basis_forward.y * 50.0f;
                direction_scaled.z = game->overlay_0.transform.basis_forward.z * 50.0f;
                staged_position.x = direction_scaled.x + game->overlay_0.transform.position.x;
                staged_position.y = direction_scaled.y + game->overlay_0.transform.position.y;
                staged_position.z = direction_scaled.z + game->overlay_0.transform.position.z;
                Vector3* sprite_position = &entry->sprite->position;
                *sprite_position = staged_position;

                Vector3* sprite_velocity = &entry->sprite->velocity;
                *sprite_velocity = entry->velocity;

                Vector3 velocity_scaled;
                velocity_scaled.x = entry->velocity.x * 10.0f;
                velocity_scaled.y = entry->velocity.y * 10.0f;
                velocity_scaled.z = entry->velocity.z * 10.0f;
                sprite_position = &entry->sprite->position;
                sprite_position->x = velocity_scaled.x + sprite_position->x;
                sprite_position->y = velocity_scaled.y + sprite_position->y;
                sprite_position->z = velocity_scaled.z + sprite_position->z;
                entry->travel_distance =
                    entry->speed * 10.0f + entry->travel_distance;
            }

            result = entry->sprite;
            ++i;
            entry->sprite->color.a =
                (entry->travel_distance - 2.0f) * entry->alpha_scale *
                0.0114285713f * fade_alpha;
        } while (i < count);
    }
    return result;
}
