// set_snail_weapon @ 0x445920 (thiscall, ret 0x4)

#include "audio_system.h"
#include "player.h"

void Snail::set_snail_weapon(int movement_flags)
{
    char changed;
    int state0;
    int state1;
    int state2;

    changed = 0;

    switch (movement_flags) {
    case 1:
        state0 = 0;
        state1 = 0;
        state2 = 1;
        break;
    case 2:
        state0 = 1;
        state2 = 0;
        state1 = 1;
        break;
    case 4:
        state1 = 1;
        state0 = 1;
        state2 = 1;
        break;
    case 8:
        state0 = 0;
        state1 = 2;
        state2 = 0;
        break;
    case 16:
    case 144:
        state0 = 2;
        state2 = 0;
        state1 = 2;
        break;
    case 32:
    case 64:
    case 192:
        state0 = 0;
        state1 = 0;
        state2 = 3;
        break;
    default:
        state0 = movement_flags;
        state1 = movement_flags;
        break;
    }

    int selected_state = weapon_channels[0].selected_state;
    unsigned char immediate = 1;
    if (selected_state != state0) {
        int selected_delta = selected_state - 1;
        if (selected_delta != 0) {
            if (selected_delta != 1)
                goto apply_channel0_state;
            weapon_channels[0].set_weapon_animation(4, 1, 8);
        } else {
            weapon_channels[0].set_weapon_animation(1, 1, 8);
        }
        immediate = 0;

apply_channel0_state:
        if (state0 != 0) {
            if (state0 == 1) {
                weapon_channels[0].set_weapon_animation(1, immediate, 4);
                weapon_channels[0].set_weapon_animation(0, 0, -1);
            } else if (state0 == 2) {
                weapon_channels[0].set_weapon_animation(4, immediate, 4);
                weapon_channels[0].set_weapon_animation(3, 0, -1);
            }
        } else {
            weapon_channels[0].set_weapon_animation(-1, 0, -1);
        }

        weapon_channels[0].selected_state = state0;
        changed = 1;
    }

    selected_state = weapon_channels[1].selected_state;
    immediate = 1;
    if (selected_state == state1)
        goto channel2;

    {
        int selected_delta = selected_state - 1;
        if (selected_delta == 0) {
            weapon_channels[1].set_weapon_animation(1, 1, 8);
            goto channel1_cleared;
        }
        if (selected_delta == 1) {
            weapon_channels[1].set_weapon_animation(4, 1, 8);
channel1_cleared:
            immediate = 0;
        }
    }

    if (state1 != 0) {
        if (state1 == 1) {
            weapon_channels[1].set_weapon_animation(1, immediate, 4);
            weapon_channels[1].set_weapon_animation(0, 0, -1);
        } else if (state1 == 2) {
            weapon_channels[1].set_weapon_animation(4, immediate, 4);
            weapon_channels[1].set_weapon_animation(3, 0, -1);
        }
    } else {
        weapon_channels[1].set_weapon_animation(-1, 0, -1);
    }

    weapon_channels[1].selected_state = state1;
    changed = 1;

channel2:
    selected_state = weapon_channels[2].selected_state;
    immediate = 1;
    if (selected_state == state2) {
        if (changed != 0)
            g_sound_effect_manager.play_sound_effect(25);
        return;
    }

    {
        int selected_delta = selected_state - 1;
        if (selected_delta == 0) {
            weapon_channels[2].set_weapon_animation(1, 1, 8);
            goto channel2_cleared;
        }
        if (selected_delta == 2) {
            weapon_channels[2].set_weapon_animation(4, 1, 8);
channel2_cleared:
            immediate = 0;
        }
    }

    if (state2 != 0) {
        if (state2 == 1) {
            weapon_channels[2].set_weapon_animation(1, immediate, 4);
            weapon_channels[2].set_weapon_animation(0, 0, -1);
            weapon_channels[2].selected_state = state2;
            g_sound_effect_manager.play_sound_effect(25);
            return;
        }
        if (state2 == 3) {
            weapon_channels[2].set_weapon_animation(4, immediate, 4);
            weapon_channels[2].set_weapon_animation(3, 0, -1);
            weapon_channels[2].selected_state = state2;
            g_sound_effect_manager.play_sound_effect(25);
            return;
        }
    } else {
        weapon_channels[2].set_weapon_animation(-1, 0, -1);
    }

    weapon_channels[2].selected_state = state2;
    g_sound_effect_manager.play_sound_effect(25);
}
