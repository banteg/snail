// set_snail_weapon @ 0x445920 (thiscall, ret 0x4)

#include "audio_system.h"
#include "player.h"

void cRSnail::SetWeapon(int shoot_flags)
{
    bool any_channel_changed;
    int target_channel_0_state;
    int target_channel_1_state;
    int target_channel_2_state;
    int selected_state;
    bool transition_immediate;

    any_channel_changed = 0;

    switch (shoot_flags) {
    case 1:
        target_channel_0_state = 0;
        target_channel_1_state = 0;
        target_channel_2_state = 1;
        break;
    case 2:
        target_channel_0_state = 1;
        target_channel_1_state = 1;
        target_channel_2_state = 0;
        break;
    case 4:
        target_channel_0_state = 1;
        target_channel_1_state = 1;
        target_channel_2_state = 1;
        break;
    case 8:
        target_channel_0_state = 0;
        target_channel_1_state = 2;
        target_channel_2_state = 0;
        break;
    case 16:
        target_channel_0_state = 2;
        target_channel_1_state = 2;
        target_channel_2_state = 0;
        break;
    case 32:
        target_channel_0_state = 0;
        target_channel_1_state = 0;
        target_channel_2_state = 3;
        break;
    case 64:
        target_channel_0_state = 0;
        target_channel_1_state = 0;
        target_channel_2_state = 3;
        break;
    case 192:
        target_channel_0_state = 0;
        target_channel_1_state = 0;
        target_channel_2_state = 3;
        break;
    case 144:
        target_channel_0_state = 2;
        target_channel_1_state = 2;
        target_channel_2_state = 0;
        break;
    }

    selected_state = weapon_channels[0].selected_state;
    transition_immediate = 1;
    if (selected_state != target_channel_0_state) {
        switch (selected_state) {
        case 1:
            weapon_channels[0].SetAnimation(
                1, 1, OBJECT_ANIMATION_MODE_ONCE_REVERSE);
            transition_immediate = 0;
            break;
        case 2:
            weapon_channels[0].SetAnimation(
                4, 1, OBJECT_ANIMATION_MODE_ONCE_REVERSE);
            transition_immediate = 0;
            break;
        }

        switch (target_channel_0_state) {
        case 0:
            weapon_channels[0].SetAnimation(
                ANIM_MANAGER_HIDE_ANIMATION_ID,
                0,
                OBJECT_ANIMATION_MODE_UNCHANGED);
            break;
        case 1:
            weapon_channels[0].SetAnimation(
                1, transition_immediate, OBJECT_ANIMATION_MODE_ONCE);
            weapon_channels[0].SetAnimation(
                0, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
            break;
        case 2:
            weapon_channels[0].SetAnimation(
                4, transition_immediate, OBJECT_ANIMATION_MODE_ONCE);
            weapon_channels[0].SetAnimation(
                3, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
            break;
        }

        weapon_channels[0].selected_state = target_channel_0_state;
        any_channel_changed = 1;
    }

    selected_state = weapon_channels[1].selected_state;
    transition_immediate = 1;
    if (selected_state != target_channel_1_state) {
        switch (selected_state) {
        case 1:
            weapon_channels[1].SetAnimation(
                1, 1, OBJECT_ANIMATION_MODE_ONCE_REVERSE);
            transition_immediate = 0;
            break;
        case 2:
            weapon_channels[1].SetAnimation(
                4, 1, OBJECT_ANIMATION_MODE_ONCE_REVERSE);
            transition_immediate = 0;
            break;
        }

        switch (target_channel_1_state) {
        case 0:
            weapon_channels[1].SetAnimation(
                ANIM_MANAGER_HIDE_ANIMATION_ID,
                0,
                OBJECT_ANIMATION_MODE_UNCHANGED);
            break;
        case 1:
            weapon_channels[1].SetAnimation(
                1, transition_immediate, OBJECT_ANIMATION_MODE_ONCE);
            weapon_channels[1].SetAnimation(
                0, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
            break;
        case 2:
            weapon_channels[1].SetAnimation(
                4, transition_immediate, OBJECT_ANIMATION_MODE_ONCE);
            weapon_channels[1].SetAnimation(
                3, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
            break;
        }

        weapon_channels[1].selected_state = target_channel_1_state;
        any_channel_changed = 1;
    }

    selected_state = weapon_channels[2].selected_state;
    transition_immediate = 1;
    if (selected_state != target_channel_2_state) {
        switch (selected_state) {
        case 1:
            weapon_channels[2].SetAnimation(
                1, 1, OBJECT_ANIMATION_MODE_ONCE_REVERSE);
            transition_immediate = 0;
            break;
        case 3:
            weapon_channels[2].SetAnimation(
                4, 1, OBJECT_ANIMATION_MODE_ONCE_REVERSE);
            transition_immediate = 0;
        }

        switch (target_channel_2_state) {
        case 0:
            weapon_channels[2].SetAnimation(
                ANIM_MANAGER_HIDE_ANIMATION_ID,
                0,
                OBJECT_ANIMATION_MODE_UNCHANGED);
            break;
        case 1:
            weapon_channels[2].SetAnimation(
                1, transition_immediate, OBJECT_ANIMATION_MODE_ONCE);
            weapon_channels[2].SetAnimation(
                0, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
            break;
        case 3:
            weapon_channels[2].SetAnimation(
                4, transition_immediate, OBJECT_ANIMATION_MODE_ONCE);
            weapon_channels[2].SetAnimation(
                3, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
            break;
        }

        weapon_channels[2].selected_state = target_channel_2_state;
        any_channel_changed = 1;
    }

    if (any_channel_changed != 0) {
        g_sound_effect_manager.Play(25);
    }
}
