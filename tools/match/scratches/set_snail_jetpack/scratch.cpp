// set_snail_jetpack @ 0x445860 (thiscall, ret 0x4)

#include "audio_system.h"
#include "presentation_animation_channel.h"

class PlayerPresentationController {
public:
    void set_snail_jetpack(int state);

    char unknown_000[0x11e0];
    PresentationAnimationChannel jetpack_channel; // +0x11e0
};

void PlayerPresentationController::set_snail_jetpack(int state)
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
    unsigned char immediate = 1;
    if (selected_state != target_state) {
        if (selected_state == 4) {
            jetpack_channel.set_weapon_animation(1, 1, 8);
            immediate = 0;
            g_sound_effect_manager.play_sound_effect(26);
        }

        if (target_state != 0) {
            if (target_state == 4) {
                jetpack_channel.set_weapon_animation(1, immediate, target_state);
                jetpack_channel.set_weapon_animation(0, 0, -1);
                g_sound_effect_manager.play_sound_effect(16);
                jetpack_channel.selected_state = target_state;
                return;
            }
        } else {
            jetpack_channel.set_weapon_animation(-1, 0, -1);
        }

        jetpack_channel.selected_state = target_state;
    }
}
