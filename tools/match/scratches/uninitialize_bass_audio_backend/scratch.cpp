// uninitialize_bass_audio_backend @ 0x4496d0

typedef int (__stdcall* BassStopFn)();
typedef int (__stdcall* BassFreeFn)();

extern BassStopFn g_bass_stop; // 0x753bfc
extern BassFreeFn g_bass_free; // 0x7537d8
extern int g_bass_module; // 0x753c90

extern int __cdecl report_errorf(char* format, ...);
extern int __cdecl delete_file_path_with_directory_walk(char* path);
extern "C" __declspec(dllimport) int __stdcall FreeLibrary(int module);

void uninitialize_bass_audio_backend()
{
    g_bass_stop();
    if (g_bass_free() == 0) {
        report_errorf("Cannot Free BASS_Free()");
    }
    if (FreeLibrary(g_bass_module) == 0) {
        report_errorf("Cannot Free bass.dll library");
    }
    delete_file_path_with_directory_walk("tBass.dll");
}
