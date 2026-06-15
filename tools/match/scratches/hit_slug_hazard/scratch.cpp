// hit_slug_hazard @ 0x43f620 (thiscall, ret 0x4)

#include "slug_hazard_types.h"

int next_math_random_value();

void SlugHazardRuntime::hit_slug_hazard(int damage)
{
    hit_points -= damage;
    if (hit_points < 0) {
        hit_points = 0;
        kill_slug_hazard();
        return;
    }

    hit_flash_pending = 1;
    int variant = (int)((float)next_math_random_value() * -0.000091552734f);
    play_slug_voice(36 - variant);
}
