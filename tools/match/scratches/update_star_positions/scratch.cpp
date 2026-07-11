// update_star_positions @ 0x434800 (thiscall, ret 0x4)

#include "game_root.h"
#include "star_manager.h"

extern char* g_game_base; // data_4df904

inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

void StarManager::update_star_positions(float fade_alpha)
{
    int i = 0;
    if (count > 0) {
        do {
            entries[i].travel_distance = entries[i].speed + entries[i].travel_distance;
            if (entries[i].travel_distance > 35.0f) {
                float* travel_distance = &entries[i].travel_distance;
                *travel_distance = 0.0f;
                entries[i].sprite->facing_refresh_progress = 0.0f;

                GameRoot* game = (GameRoot*)g_game_base;
                entries[i].sprite->position =
                    game->overlay_0.transform.basis_forward * 50.0f +
                    game->overlay_0.transform.position;
                entries[i].sprite->velocity = entries[i].velocity;
                entries[i].sprite->position += entries[i].velocity * 10.0f;
                entries[i].travel_distance =
                    entries[i].speed * 10.0f + entries[i].travel_distance;
            }

            entries[i].sprite->color.a =
                (entries[i].travel_distance - 2.0f) * entries[i].alpha_scale *
                0.0114285713f * fade_alpha;
            ++i;
        } while (i < count);
    }
}
