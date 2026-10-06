// AudioBackend::stop_audio_backend @ 0x449b90 (thiscall)

#include "audio_system.h"

int AudioBackend::stop_audio_backend()
{
    return g_bass_stop();
}
