// AudioBackend::stop_sound_sample_handle @ 0x449a10

#include "audio_system.h"

int AudioBackend::stop_sound_sample_handle(int sample_handle)
{
    return g_bass_sample_stop(sample_handle);
}
