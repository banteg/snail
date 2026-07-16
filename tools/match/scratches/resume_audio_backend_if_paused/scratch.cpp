// resume_audio_backend_if_paused @ 0x449ba0 (thiscall)

#include "audio_system.h"

void AudioBackend::resume_audio_backend_if_paused()
{
    if (is_paused == 1) {
        g_bass_start();
        is_paused = 0;
    }
}
