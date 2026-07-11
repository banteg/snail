// update_warning @ 0x446f80 (thiscall, ret)
// The damage-warning actor: state 1 holds the overlay alpha near full
// (0.99900001f, bits 1065336439) while the phase fills; state 2 fades the
// first half then holds zero, replaying sound 50 on wrap back to 1.

#include "audio_system.h"
#include "game_root.h"
#include "warning_actor.h"

extern GameRoot* g_game; // data_4df904

void WarningActor::update_warning()
{
    if (!g_game->subgame.subgame_pause_gate && state) {
        float advanced;
        switch (state) {
        case 2:
            if (phase < 0.5f)
                border->warning_overlay_alpha = 1.0f - (phase + phase);
            else
                border->warning_overlay_alpha = 0;
            advanced = phase_step + phase;
            phase = advanced;
            if (advanced > 1.0f) {
                phase = 0.0f;
                state = 1;
                g_sound_effect_manager.play_sound_effect(50);
            }
            break;
        case 1:
            border->warning_overlay_alpha = 0.99900001f;
            advanced = phase_step + phase;
            phase = advanced;
            if (advanced > 1.0f) {
                phase = 0.0f;
                state = 2;
            }
            break;
        }
    }
}
