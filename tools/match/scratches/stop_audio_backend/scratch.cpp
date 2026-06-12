// stop_audio_backend @ 0x449b90 (stdcall)

typedef int (__stdcall* BassStopFn)();

extern BassStopFn g_bass_stop; // 0x753bfc

int __stdcall stop_audio_backend()
{
    return g_bass_stop();
}
