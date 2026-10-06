// set_global_stream_volume_config @ 0x449b70 (thiscall, ret 0x4)

#include "audio_system.h"

int AudioBackend::set_global_stream_volume_config(float volume)
{
    return g_bass_set_config(5, (int)(volume * 100.0f));
}
