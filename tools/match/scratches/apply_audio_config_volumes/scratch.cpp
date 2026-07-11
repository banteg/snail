// apply_audio_config_volumes @ 0x41b070

#include "audio_system.h"
#include "runtime_config.h"

extern float g_stream_volume_scale; // 0x753c64

int apply_audio_config_volumes()
{
    g_audio_backend.set_global_sample_volume_config(g_runtime_config.sample_volume);
    return g_audio_backend.set_global_stream_volume_config(
        g_runtime_config.stream_volume * g_stream_volume_scale);
}
