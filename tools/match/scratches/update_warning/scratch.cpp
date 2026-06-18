// update_warning @ 0x446f80 (thiscall, ret)
// The damage-warning actor: state 1 holds the overlay alpha near full
// (0.99900001f, bits 1065336439) while the phase fills; state 2 fades the
// first half then holds zero, replaying sound 50 on wrap back to 1.

#include "audio_system.h"
#include "warning_actor.h"

struct Game {
    char unknown_00[0x74621];
    unsigned char pause_gate; // +0x74621
};

extern Game* volatile g_game; // data_4df904

void WarningActor::update_warning()
{
    if (!g_game->pause_gate && state) {
        if (state == 2) {
            if (phase >= 0.5f)
                border->warning_overlay_alpha = 0;
            else
                border->warning_overlay_alpha = 1.0f - (phase + phase);
            float advanced = phase_step + phase;
            phase = advanced;
            if (advanced > 1.0f) {
                phase = 0.0f;
                state = 1;
                g_sound_effect_manager.play_sound_effect(50);
            }
        } else if (state == 1) {
            border->warning_overlay_alpha = 0.99900001f;
            float advanced = phase_step + phase;
            phase = advanced;
            if (advanced > 1.0f) {
                phase = 0.0f;
                state = 2;
            }
        }
    }
}
