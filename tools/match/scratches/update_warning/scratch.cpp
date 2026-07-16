// update_warning @ 0x446f80 (thiscall, ret)
// The damage-warning actor: state 1 holds the border's hot-text alpha near full
// (0.99900001f, bits 1065336439) while the phase fills; state 2 fades the
// first half then holds zero, replaying sound 50 on wrap back to 1.

#include "audio_system.h"
#include "game_root.h"
#include "warning.h"


void Warning::update_warning()
{
    if (!g_game->subgame.subgame_pause_gate && state) {
        float advanced;
        switch (state) {
        case WARNING_STATE_FADING:
            if (phase < 0.5f)
                border->hot_text_color.a = 1.0f - (phase + phase);
            else
                border->hot_text_color.a = 0;
            advanced = phase_step + phase;
            phase = advanced;
            if (advanced > 1.0f) {
                phase = 0.0f;
                state = WARNING_STATE_OPAQUE;
                g_sound_effect_manager.play_sound_effect(50);
            }
            break;
        case WARNING_STATE_OPAQUE:
            border->hot_text_color.a = 0.99900001f;
            advanced = phase_step + phase;
            phase = advanced;
            if (advanced > 1.0f) {
                phase = 0.0f;
                state = WARNING_STATE_FADING;
            }
            break;
        }
    }
}
