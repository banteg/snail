// AudioBackend::uninitialize_bass_audio_backend @ 0x4496d0

#include "audio_system.h"

extern int __cdecl report_errorf(char* format, ...);
extern int __cdecl delete_file_path_with_directory_walk(char* path);
extern "C" __declspec(dllimport) int __stdcall FreeLibrary(void* module);

void AudioBackend::uninitialize_bass_audio_backend()
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
