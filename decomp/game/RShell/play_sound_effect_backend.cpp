// play_sound_effect_backend @ 0x432df0 (cdecl)

#include "audio_system.h"

void play_sound_effect_backend(int sample_id, float gain, float pitch, float pan)
{
    if (sample_id != -1) {
        if (pan == 0.0f) {
            if (pitch == -1.0f) {
                float scaled_gain = g_audio_backend_sfx_normalization_scale * gain;
                g_audio_backend.play_registered_sound_sample_scaled(sample_id, scaled_gain);
            } else {
                float scaled_gain = g_audio_backend_sfx_normalization_scale * gain;
                g_audio_backend.play_registered_sound_sample_backend(
                    sample_id, scaled_gain, pitch);
            }
        } else {
            float scaled_gain = g_audio_backend_sfx_normalization_scale * gain;
            g_audio_backend.play_registered_sound_sample_scaled_panned(
                sample_id, scaled_gain, -1.0f, pan);
        }
    }
}
