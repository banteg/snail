// set_global_sample_volume_config @ 0x449b50 (thiscall, ret 0x4)

#include "audio_system.h"

typedef int (__stdcall* BassSetConfigFn)(int option, int value);

extern BassSetConfigFn g_bass_set_config; // 0x753c1c

int AudioBackend::set_global_sample_volume_config(float volume)
{
    return g_bass_set_config(4, (int)(volume * 100.0f));
}
