// set_snail_jetpack @ 0x445860 (thiscall, ret 0x4)

#include "audio_system.h"
#include "player.h"

void cRSnail::SetJetPack(int state)
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
            jetpack_channel.SetAnimation(
                1, 1, OBJECT_ANIMATION_MODE_ONCE_REVERSE);
            immediate = false;
            g_sound_effect_manager.Play(26);
        }

        if (target_state != 0) {
            if (target_state == 4) {
                jetpack_channel.SetAnimation(1, immediate, target_state);
                jetpack_channel.SetAnimation(
                    0, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
                g_sound_effect_manager.Play(16);
            }
        } else {
            jetpack_channel.SetAnimation(
                ANIM_MANAGER_HIDE_ANIMATION_ID,
                0,
                OBJECT_ANIMATION_MODE_UNCHANGED);
        }

        jetpack_channel.selected_state = target_state;
    }
}
