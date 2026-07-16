// AudioBackend::play_registered_sound_sample_backend @ 0x449a80

#include "audio_system.h"

void AudioBackend::play_registered_sound_sample_backend(
    int sample_id, float volume, float pitch)
{
    if (volume >= 0.0f && (volume > 1.0f || volume != 0.0f)) {
        g_bass_sample_play_ex(
            g_registered_sound_sample_handles[sample_id], 0, (int)pitch, -1, 101, 0);
    }
}
