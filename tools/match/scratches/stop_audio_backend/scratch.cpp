// AudioBackend::stop_audio_backend @ 0x449b90 (thiscall)

#include "audio_system.h"

typedef int (__stdcall* BassStopFn)();

extern BassStopFn g_bass_stop; // 0x753bfc

int AudioBackend::stop_audio_backend()
{
    return g_bass_stop();
}
