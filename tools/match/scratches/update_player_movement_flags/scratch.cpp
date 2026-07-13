// update_player_movement_flags @ 0x43a1a0 (thiscall, ret)

#include "player.h"

int Player::update_player_movement_flags()
{
    int selector = movement_flag_selector;
    movement_flags = 0;

    switch (selector) {
    case 0:
        movement_flags = 1;
        movement_fire_progress_step = 0.074074075f;
        break;
    case 1:
        movement_flags = 2;
        movement_fire_progress_step = 0.074074075f;
        break;
    case 2:
        movement_flags = 4;
        movement_fire_progress_step = 0.074074075f;
        break;
    case 3:
        movement_flags = 8;
        movement_fire_progress_step = 0.111111104f;
        break;
    case 4:
        movement_flags = 16;
        movement_fire_progress_step = 0.111111104f;
        break;
    case 5:
        movement_flags = 32;
        goto slow_fire;
    case 6:
        movement_flags = 64;
        movement_fire_progress_step = 0.13333334f;
        break;
    case 7:
        movement_flags = 192;
        movement_fire_progress_step = 0.13333334f;
        break;
    case 8:
        movement_flags = 144;
        movement_fire_progress_step = 0.111111104f;
        break;
    default:
        movement_flags = 129;
slow_fire:
        movement_fire_progress_step = 0.06666667f;
        break;
    }

    unsigned int result = movement_flags;
    if (result != previous_movement_flags) {
        presentation.set_snail_weapon(movement_flags);
        result = movement_flags;
        previous_movement_flags = result;
        return result;
    }

    previous_movement_flags = movement_flags;
    return result;
}
