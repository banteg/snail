// apply_audio_config_volumes @ 0x41b070

#include "audio_system.h"

extern float g_config_sample_volume; // 0x4df918
extern float g_config_stream_volume; // 0x4df91c
extern float g_stream_volume_scale; // 0x753c64

int apply_audio_config_volumes()
{
    g_audio_backend.set_global_sample_volume_config(g_config_sample_volume);
    return g_audio_backend.set_global_stream_volume_config(
        g_config_stream_volume * g_stream_volume_scale);
}
