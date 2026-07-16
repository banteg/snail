// AudioBackend::play_registered_sound_sample_scaled_panned @ 0x449ae0

#include "audio_system.h"

void AudioBackend::play_registered_sound_sample_scaled_panned(
    int sample_id, float volume, float pitch, float pan)
{
    if (volume >= 0.0f && (volume > 1.0f || volume != 0.0f)) {
        g_bass_sample_play_ex(
            g_registered_sound_sample_handles[sample_id],
            0,
            (int)pitch,
            -1,
            (int)pan,
            0);
    }
}
