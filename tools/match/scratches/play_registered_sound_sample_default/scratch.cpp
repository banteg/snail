// AudioBackend::play_registered_sound_sample_default @ 0x449a60

#include "audio_system.h"

typedef int (__stdcall* BassSamplePlayExFn)(
    int sample_handle, int start, int frequency, int volume, int pan, int loop);

extern int g_registered_sound_sample_handles[]; // 0x7537e0
extern BassSamplePlayExFn g_bass_sample_play_ex; // 0x7527b4

int AudioBackend::play_registered_sound_sample_default(int sample_id)
{
    return g_bass_sample_play_ex(
        g_registered_sound_sample_handles[sample_id], 0, -1, -1, 101, 1);
}
