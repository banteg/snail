// kill_slug_hazard @ 0x43f8b0 (thiscall, ret)

#include "slug_hazard_types.h"

int next_math_random_value();

class Player {
public:
    void add_subgoldy_score(int score_kind, int bonus_score);
};

struct Game {
    char unknown_00[0x3bb764];
    Player player; // +0x3bb764
};

void SlugHazardRuntime::kill_slug_hazard()
{
    if (state == 1) {
        int variant = (int)((float)next_math_random_value() * -0.000061035156f);
        play_slug_voice(28 - variant);
        float x = world_position.x;
        state = 2;
        if (x > 0.0f)
            death_toss_direction = 1;
        else
            death_toss_direction = 2;
        owner_game->player.add_subgoldy_score(1, 0);
        explode_slug_hazard();
    }
}
