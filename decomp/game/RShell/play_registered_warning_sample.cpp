// play_registered_warning_sample @ 0x432dd0

#include "audio_system.h"

int play_registered_warning_sample(int sample_id)
{
    return g_audio_backend.play_registered_sound_sample_default(sample_id);
}
