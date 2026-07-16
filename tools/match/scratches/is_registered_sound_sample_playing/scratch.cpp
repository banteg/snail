// AudioBackend::is_registered_sound_sample_playing @ 0x449a40

#include "audio_system.h"

bool AudioBackend::is_registered_sound_sample_playing(int sample_id)
{
    bool active = g_bass_channel_is_active(g_registered_sound_sample_handles[sample_id]) == 1;
    return active;
}
