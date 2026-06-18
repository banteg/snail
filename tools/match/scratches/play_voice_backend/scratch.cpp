// play_voice_backend @ 0x432e80 (cdecl)

#include "audio_system.h"

extern float g_audio_backend_voice_normalization_scale; // g_audio_backend + 0x14

void play_voice_backend(int sample_id, float gain, float pitch, float pan)
{
    if (sample_id != -1) {
        if (pan == 0.0f) {
            if (pitch == -1.0f) {
                float scaled_gain = g_audio_backend_voice_normalization_scale * gain;
                g_audio_backend.play_registered_sound_sample_scaled(sample_id, scaled_gain);
            } else {
                float scaled_gain = g_audio_backend_voice_normalization_scale * gain;
                g_audio_backend.play_registered_sound_sample_backend(
                    sample_id, scaled_gain, pitch);
            }
        } else {
            float scaled_gain = g_audio_backend_voice_normalization_scale * gain;
            g_audio_backend.play_registered_sound_sample_scaled_panned(
                sample_id, scaled_gain, -1.0f, pan);
        }
    }
}
