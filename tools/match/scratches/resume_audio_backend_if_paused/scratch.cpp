// resume_audio_backend_if_paused @ 0x449ba0 (thiscall)

typedef int (__stdcall* BassStartFn)();

extern BassStartFn g_bass_start; // 0x751660

class AudioBackend {
public:
    void resume_audio_backend_if_paused();

    char pad_00[0x18];
    unsigned char is_paused; // 0x18
};

void AudioBackend::resume_audio_backend_if_paused()
{
    if (is_paused == 1) {
        g_bass_start();
        is_paused = 0;
    }
}
