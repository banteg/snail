// set_snail_weapon @ 0x445920 (thiscall, ret 0x4)

#include "audio_system.h"
#include "player.h"

void Snail::set_snail_weapon(int movement_flags)
{
    bool changed;
    int state0;
    int state1;
    int state2;
    int selected_state;
    bool immediate;

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
    case 32:
    case 64:
    case 192:
        state0 = 0;
        state1 = 0;
        state2 = 3;
        break;
    case 16:
    case 144:
        state0 = 2;
        state2 = 0;
        state1 = 2;
        break;
    default:
        state0 = movement_flags;
        state1 = movement_flags;
        break;
    }

    selected_state = weapon_channels[0].selected_state;
    immediate = 1;
    if (selected_state != state0) {
        switch (selected_state) {
        case 1:
            weapon_channels[0].set_weapon_animation(
                1, 1, OBJECT_ANIMATION_MODE_ONCE_REVERSE);
            immediate = 0;
            break;
        case 2:
            weapon_channels[0].set_weapon_animation(
                4, 1, OBJECT_ANIMATION_MODE_ONCE_REVERSE);
            immediate = 0;
            break;
        }

        switch (state0) {
        case 0:
            weapon_channels[0].set_weapon_animation(
                ANIM_MANAGER_HIDE_ANIMATION_ID,
                0,
                OBJECT_ANIMATION_MODE_UNCHANGED);
            break;
        case 1:
            weapon_channels[0].set_weapon_animation(
                1, immediate, OBJECT_ANIMATION_MODE_ONCE);
            weapon_channels[0].set_weapon_animation(
                0, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
            break;
        case 2:
            weapon_channels[0].set_weapon_animation(
                4, immediate, OBJECT_ANIMATION_MODE_ONCE);
            weapon_channels[0].set_weapon_animation(
                3, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
            break;
        }

        weapon_channels[0].selected_state = state0;
        changed = 1;
    }

    selected_state = weapon_channels[1].selected_state;
    immediate = 1;
    if (selected_state == state1)
        goto channel2;

    switch (selected_state) {
    case 1:
        weapon_channels[1].set_weapon_animation(
            1, 1, OBJECT_ANIMATION_MODE_ONCE_REVERSE);
        immediate = 0;
        break;
    case 2:
        weapon_channels[1].set_weapon_animation(
            4, 1, OBJECT_ANIMATION_MODE_ONCE_REVERSE);
        immediate = 0;
        break;
    }

    switch (state1) {
    case 0:
        weapon_channels[1].set_weapon_animation(
            ANIM_MANAGER_HIDE_ANIMATION_ID,
            0,
            OBJECT_ANIMATION_MODE_UNCHANGED);
        break;
    case 1:
        weapon_channels[1].set_weapon_animation(
            1, immediate, OBJECT_ANIMATION_MODE_ONCE);
        weapon_channels[1].set_weapon_animation(
            0, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
        break;
    case 2:
        weapon_channels[1].set_weapon_animation(
            4, immediate, OBJECT_ANIMATION_MODE_ONCE);
        weapon_channels[1].set_weapon_animation(
            3, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
        break;
    }

    weapon_channels[1].selected_state = state1;
    changed = 1;

channel2:
    selected_state = weapon_channels[2].selected_state;
    immediate = 1;
    if (selected_state != state2) {
        switch (selected_state) {
        case 1:
            weapon_channels[2].set_weapon_animation(
                1, 1, OBJECT_ANIMATION_MODE_ONCE_REVERSE);
            immediate = 0;
            break;
        case 3:
            weapon_channels[2].set_weapon_animation(
                4, 1, OBJECT_ANIMATION_MODE_ONCE_REVERSE);
            immediate = 0;
        }

        switch (state2) {
        case 0:
            weapon_channels[2].set_weapon_animation(
                ANIM_MANAGER_HIDE_ANIMATION_ID,
                0,
                OBJECT_ANIMATION_MODE_UNCHANGED);
            break;
        case 1:
            weapon_channels[2].set_weapon_animation(
                1, immediate, OBJECT_ANIMATION_MODE_ONCE);
            weapon_channels[2].set_weapon_animation(
                0, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
            weapon_channels[2].selected_state = state2;
            g_sound_effect_manager.play_sound_effect(25);
            return;
        case 3:
            weapon_channels[2].set_weapon_animation(
                4, immediate, OBJECT_ANIMATION_MODE_ONCE);
            weapon_channels[2].set_weapon_animation(
                3, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
            weapon_channels[2].selected_state = state2;
            g_sound_effect_manager.play_sound_effect(25);
            return;
        }

        weapon_channels[2].selected_state = state2;
        g_sound_effect_manager.play_sound_effect(25);
    } else if (changed != 0) {
        g_sound_effect_manager.play_sound_effect(25);
    }
}
