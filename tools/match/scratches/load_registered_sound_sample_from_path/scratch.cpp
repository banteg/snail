// load_registered_sound_sample_from_path @ 0x449920 (thiscall, ret 0xc)

#include "audio_system.h"

typedef int (__stdcall* BassSampleLoadFn)(
    int from_memory, char* path_or_bytes, int offset, int byte_count, int max_instances, int flags);

extern BassSampleLoadFn g_bass_sample_load; // 0x7537cc
extern int g_registered_sound_sample_handles[]; // 0x7537e0

int debug_report_stub(char* format, ...); // @ 0x449c00, stripped in release

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
