// pause_audio_backend_if_running @ 0x449bc0 (thiscall)

#include "audio_system.h"

char AudioBackend::pause_audio_backend_if_running()
{
    char result = is_paused;
    if (result == 0) {
        result = g_bass_pause();
        is_paused = 1;
    }
    return result;
}
