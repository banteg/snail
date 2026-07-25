// update_player_movement_flags @ 0x43a1a0 (thiscall, ret)

#include "player.h"

void Player::SetShootFlags()
{
    int selector = movement_flag_selector;
    movement_flags = 0;

    switch (selector) {
    case 0:
        movement_flags = 1;
        shoot_cooldown_step = 0.074074075f;
        break;
    case 1:
        movement_flags = 2;
        shoot_cooldown_step = 0.074074075f;
        break;
    case 2:
        movement_flags = 4;
        shoot_cooldown_step = 0.074074075f;
        break;
    case 3:
        movement_flags = 8;
        shoot_cooldown_step = 0.111111104f;
        break;
    case 4:
        movement_flags = 16;
        shoot_cooldown_step = 0.111111104f;
        break;
    case 5:
        movement_flags = 32;
        goto slow_fire;
    case 6:
        movement_flags = 64;
        shoot_cooldown_step = 0.13333334f;
        break;
    case 7:
        movement_flags = 192;
        shoot_cooldown_step = 0.13333334f;
        break;
    case 8:
        movement_flags = 144;
        shoot_cooldown_step = 0.111111104f;
        break;
    default:
        movement_flags = 129;
slow_fire:
        shoot_cooldown_step = 0.06666667f;
        break;
    }

    if (movement_flags != previous_movement_flags) {
        presentation.set_snail_weapon(movement_flags);
        previous_movement_flags = movement_flags;
        return;
    }

    previous_movement_flags = movement_flags;
}
