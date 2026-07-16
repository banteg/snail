// AudioBackend::play_registered_sound_sample_default @ 0x449a60

#include "audio_system.h"

int AudioBackend::play_registered_sound_sample_default(int sample_id)
{
    return g_bass_sample_play_ex(
        g_registered_sound_sample_handles[sample_id], 0, -1, -1, 101, 1);
}
