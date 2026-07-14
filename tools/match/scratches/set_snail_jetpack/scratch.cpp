// set_snail_jetpack @ 0x445860 (thiscall, ret 0x4)

#include "audio_system.h"
#include "player.h"

void Snail::set_snail_jetpack(int state)
{
    int input_state = state;
    register int target_state;

    switch (input_state) {
    case 0:
        target_state = 0;
        break;
    case 1:
        target_state = 4;
        break;
    default:
        target_state = input_state;
        break;
    }

    int selected_state = jetpack_channel.selected_state;
    bool immediate = true;
    if (selected_state != target_state) {
        if (selected_state == 4) {
            jetpack_channel.set_weapon_animation(
                1, 1, OBJECT_ANIMATION_MODE_ONCE_REVERSE);
            immediate = false;
            g_sound_effect_manager.play_sound_effect(26);
        }

        if (target_state != 0) {
            if (target_state == 4) {
                jetpack_channel.set_weapon_animation(1, immediate, target_state);
                jetpack_channel.set_weapon_animation(
                    0, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
                g_sound_effect_manager.play_sound_effect(16);
            }
        } else {
            jetpack_channel.set_weapon_animation(
                ANIM_MANAGER_HIDE_ANIMATION_ID,
                0,
                OBJECT_ANIMATION_MODE_UNCHANGED);
        }

        jetpack_channel.selected_state = target_state;
    }
}
