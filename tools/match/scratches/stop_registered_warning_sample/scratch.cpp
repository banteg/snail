// stop_registered_warning_sample @ 0x432de0

#include "audio_system.h"

int stop_registered_warning_sample(int sample_handle)
{
    return g_audio_backend.stop_sound_sample_handle(sample_handle);
}
