// AudioBackend::play_registered_sound_sample_scaled @ 0x4499a0

#include "audio_system.h"

void AudioBackend::play_registered_sound_sample_scaled(int sample_id, float volume)
{
    if (volume >= 0.0f) {
        if (volume > 1.0f) {
            volume = 1.0f;
        } else {
            if (volume == 0.0f) {
                return;
            }
        }
        g_bass_sample_play_ex(
            g_registered_sound_sample_handles[sample_id],
            0,
            -1,
            (int)(volume * 100.0f),
            0,
            -1);
    }
}
