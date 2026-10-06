// stop_music_stream @ 0x4498d0 (thiscall)

#include "audio_system.h"

void AudioBackend::stop_music_stream()
{
    if (music_stream_active) {
        if (g_active_music_stream_sync != 0) {
            g_bass_channel_remove_sync(
                g_active_music_stream, g_active_music_stream_sync);
            g_active_music_stream_sync = 0;
        }
        g_bass_channel_stop(g_active_music_stream);
        g_bass_stream_free(g_active_music_stream);
        music_stream_active = 0;
    }
}
