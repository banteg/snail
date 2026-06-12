// stop_music_stream @ 0x4498d0 (thiscall)

typedef int (__stdcall* BassChannelRemoveSyncFn)(int handle, int sync);
typedef int (__stdcall* BassChannelStopFn)(int handle);
typedef int (__stdcall* BassStreamFreeFn)(int handle);

extern int g_active_music_stream; // 0x753c20
extern int g_active_music_stream_sync; // 0x751680
extern BassChannelRemoveSyncFn g_bass_channel_remove_sync; // 0x75165c
extern BassChannelStopFn g_bass_channel_stop; // 0x753be4
extern BassStreamFreeFn g_bass_stream_free; // 0x753cb0

class AudioBackend
{
public:
    unsigned char music_stream_active; // 0x0

    void stop_music_stream();
};

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
