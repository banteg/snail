// load_registered_sound_sample_from_path @ 0x449920 (thiscall, ret 0xc)

#include "audio_system.h"
#include "rdebug.h"

int AudioBackend::load_registered_sound_sample_from_path(
    char* path, int sample_id, int normalization_class)
{
    int sample_handle =
        g_bass_sample_load(0, path, 0, 0, normalization_class, 0x20010);
    g_registered_sound_sample_handles[sample_id] = sample_handle;
    if (sample_handle == 0) {
        return debug_report_stub("Bass Sample Load Fail %s\n", path);
    }

    return sample_handle;
}
