// apply_audio_config_volumes @ 0x41b070

#include "audio_system.h"
#include "options.h"
#include "runtime_config.h"

extern float g_stream_volume_scale; // 0x753c64

void Options::apply_audio_config_volumes()
{
    g_audio_backend.set_global_sample_volume_config(g_runtime_config.sample_volume);
    g_audio_backend.set_global_stream_volume_config(
        g_runtime_config.stream_volume * g_stream_volume_scale);
}
