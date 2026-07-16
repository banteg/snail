// AudioBackend::stop_registered_sound_sample @ 0x449a20

#include "audio_system.h"

void AudioBackend::stop_registered_sound_sample(int sample_id)
{
    g_bass_sample_stop(g_registered_sound_sample_handles[sample_id]);
}
