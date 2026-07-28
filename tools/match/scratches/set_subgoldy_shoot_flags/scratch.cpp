// set_subgoldy_shoot_flags @ 0x43a1a0, authored cRSubGoldy::SetShootFlags()

#include "player.h"

void cRSubGoldy::SetShootFlags()
{
    int tier = shooting_tier;
    shoot_flags = 0;

    switch (tier) {
    case 0:
        shoot_flags = 1;
        shoot_cooldown_step = 0.074074075f;
        break;
    case 1:
        shoot_flags = 2;
        shoot_cooldown_step = 0.074074075f;
        break;
    case 2:
        shoot_flags = 4;
        shoot_cooldown_step = 0.074074075f;
        break;
    case 3:
        shoot_flags = 8;
        shoot_cooldown_step = 0.111111104f;
        break;
    case 4:
        shoot_flags = 16;
        shoot_cooldown_step = 0.111111104f;
        break;
    case 5:
        shoot_flags = 32;
        goto slow_fire;
    case 6:
        shoot_flags = 64;
        shoot_cooldown_step = 0.13333334f;
        break;
    case 7:
        shoot_flags = 192;
        shoot_cooldown_step = 0.13333334f;
        break;
    case 8:
        shoot_flags = 144;
        shoot_cooldown_step = 0.111111104f;
        break;
    default:
        shoot_flags = 129;
slow_fire:
        shoot_cooldown_step = 0.06666667f;
        break;
    }

    unsigned int current_flags = shoot_flags;
    unsigned int selected_flags = previous_shoot_flags;
    if (current_flags != selected_flags) {
        presentation.set_snail_weapon(current_flags);
        selected_flags = shoot_flags;
    }

    previous_shoot_flags = selected_flags;
}
