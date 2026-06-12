// pause_audio_backend_if_running @ 0x449bc0 (thiscall)

typedef int (__stdcall* BassPauseFn)();

extern BassPauseFn g_bass_pause; // 0x753cc0

class AudioBackend {
public:
    char pause_audio_backend_if_running();

    char pad_00[0x18];
    char is_paused; // 0x18
};

char AudioBackend::pause_audio_backend_if_running()
{
    char result = is_paused;
    if (result == 0) {
        result = g_bass_pause();
        is_paused = 1;
    }
    return result;
}
