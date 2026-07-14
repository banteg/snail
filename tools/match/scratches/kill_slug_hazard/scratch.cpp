// kill_slug_hazard @ 0x43f8b0 (thiscall, ret)

#include "slug_hazard_types.h"
#include "player.h"
#include "subgame_runtime.h"

int next_math_random_value();

void Slug::kill_slug_hazard()
{
    if (state == SUB_SLUG_STATE_ACTIVE) {
        int variant = (int)((float)next_math_random_value() * -0.000061035156f);
        play_slug_voice(28 - variant);
        float x = transform.position.x;
        state = SUB_SLUG_STATE_DEATH_TOSS_PENDING;
        if (x > 0.0f)
            death_toss_direction = SUB_SLUG_DEATH_TOSS_RIGHT;
        else
            death_toss_direction = SUB_SLUG_DEATH_TOSS_LEFT;
        owner_game->player.add_subgoldy_score(SUBGOLDY_SCORE_SLUG, 0);
        explode_slug_hazard();
    }
}
