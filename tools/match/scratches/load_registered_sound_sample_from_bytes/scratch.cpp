// load_registered_sound_sample_from_bytes @ 0x449960 (thiscall, ret 0x10)

#include "audio_system.h"

typedef int (__stdcall* BassSampleLoadFn)(
    int from_memory, char* path_or_bytes, int offset, int byte_count, int max_instances, int flags);

extern BassSampleLoadFn g_bass_sample_load; // 0x7537cc

int debug_report_stub(char* format, ...); // @ 0x449c00, stripped in release

void AudioBackend::load_registered_sound_sample_from_bytes(
    char* bytes, int byte_count, int sample_id, int normalization_class)
{
    int sample_handle =
        g_bass_sample_load(1, bytes, 0, byte_count, normalization_class, 0x20010);
    g_registered_sound_sample_handles[sample_id] = sample_handle;
    if (sample_handle == 0) {
        debug_report_stub("***ERROR:Bass Sample Load Memory Fail\n");
    }
}
