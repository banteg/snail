// initialize_bass_audio_backend @ 0x449460 (thiscall, ret 0x4)

#include "audio_system.h"

typedef int (__stdcall* BassInitFn)(
    int device, int frequency, int flags, void* hwnd, void* clsid);
typedef int (__stdcall* BassSetConfigFn)(int option, int value);
typedef int (__stdcall* BassProcFn)();

extern int g_active_music_stream; // 0x753c20
extern int g_active_music_stream_sync; // 0x751680
extern int g_bass_module; // 0x753c90

extern BassInitFn g_bass_init; // 0x753c08
extern BassSetConfigFn g_bass_set_config; // 0x753c1c
extern BassProcFn g_bass_free; // 0x7537d8
extern BassProcFn g_bass_update; // 0x751698
extern BassProcFn g_bass_stream_create_file; // 0x753bf8
extern BassProcFn g_bass_channel_play; // 0x7517a0
extern BassProcFn g_bass_stream_prebuf; // 0x751670
extern BassProcFn g_bass_channel_stop; // 0x753be4
extern BassProcFn g_bass_stream_free; // 0x753cb0
extern BassProcFn g_bass_sample_load; // 0x7537cc
extern BassProcFn g_bass_sample_play_ex; // 0x7527b4
extern BassProcFn g_bass_sample_stop; // 0x753c94
extern BassProcFn g_bass_stop; // 0x753bfc
extern BassProcFn g_bass_start; // 0x751660
extern BassProcFn g_bass_pause; // 0x753cc0
extern BassProcFn g_bass_channel_bytes2_seconds; // 0x75162c
extern BassProcFn g_bass_channel_get_level; // 0x753cbc
extern BassProcFn g_bass_channel_get_data; // 0x753c18
extern BassProcFn g_bass_channel_set_sync; // 0x753cc4
extern BassProcFn g_bass_channel_get_position; // 0x753c98
extern BassProcFn g_bass_error_get_code; // 0x751674
extern BassProcFn g_bass_channel_remove_sync; // 0x75165c
extern BassProcFn g_bass_sample_is_active; // 0x753ca8

extern char* load_file_bytes(char* file_name, int* out_size);
extern int write_file_bytes(char* file_name, char* bytes, int byte_count);
extern void free_tracked_memory(void* ptr);
extern int report_errorf(char* format, ...);

extern "C" __declspec(dllimport) int __stdcall LoadLibraryA(char* library_name);
extern "C" __declspec(dllimport) int __stdcall GetProcAddress(int module, char* name);

char AudioBackend::initialize_bass_audio_backend(void* hwnd)
{
    int byte_count;

    char* file_bytes;

    g_cached_music_path[0] = 0;
    is_paused = 0;

    file_bytes = load_file_bytes("Bass.dll", &byte_count);
    write_file_bytes("tBass.dll", file_bytes, byte_count);
    free_tracked_memory(file_bytes);

    g_bass_module = LoadLibraryA("tBass.dll");
    g_bass_init = (BassInitFn)GetProcAddress(g_bass_module, "BASS_Init");
    g_bass_set_config = (BassSetConfigFn)GetProcAddress(g_bass_module, "BASS_SetConfig");
    g_bass_free = (BassProcFn)GetProcAddress(g_bass_module, "BASS_Free");
    g_bass_update = (BassProcFn)GetProcAddress(g_bass_module, "BASS_Update");
    g_bass_stream_create_file =
        (BassProcFn)GetProcAddress(g_bass_module, "BASS_StreamCreateFile");
    g_bass_channel_play = (BassProcFn)GetProcAddress(g_bass_module, "BASS_StreamPlay");
    g_bass_stream_prebuf = (BassProcFn)GetProcAddress(g_bass_module, "BASS_StreamPreBuf");
    g_bass_channel_stop = (BassProcFn)GetProcAddress(g_bass_module, "BASS_ChannelStop");
    g_bass_stream_free = (BassProcFn)GetProcAddress(g_bass_module, "BASS_StreamFree");
    g_bass_sample_load = (BassProcFn)GetProcAddress(g_bass_module, "BASS_SampleLoad");
    g_bass_sample_play_ex = (BassProcFn)GetProcAddress(g_bass_module, "BASS_SamplePlayEx");
    g_bass_sample_stop = (BassProcFn)GetProcAddress(g_bass_module, "BASS_SampleStop");
    g_bass_set_config = (BassSetConfigFn)GetProcAddress(g_bass_module, "BASS_SetConfig");
    g_bass_stop = (BassProcFn)GetProcAddress(g_bass_module, "BASS_Stop");
    g_bass_start = (BassProcFn)GetProcAddress(g_bass_module, "BASS_Start");
    g_bass_pause = (BassProcFn)GetProcAddress(g_bass_module, "BASS_Pause");
    g_bass_channel_bytes2_seconds =
        (BassProcFn)GetProcAddress(g_bass_module, "BASS_ChannelBytes2Seconds");
    g_bass_channel_get_level =
        (BassProcFn)GetProcAddress(g_bass_module, "BASS_ChannelGetLevel");
    g_bass_channel_get_data =
        (BassProcFn)GetProcAddress(g_bass_module, "BASS_ChannelGetData");
    g_bass_channel_set_sync =
        (BassProcFn)GetProcAddress(g_bass_module, "BASS_ChannelSetSync");
    g_bass_channel_get_position =
        (BassProcFn)GetProcAddress(g_bass_module, "BASS_ChannelGetPosition");
    g_bass_error_get_code = (BassProcFn)GetProcAddress(g_bass_module, "BASS_ErrorGetCode");
    g_bass_channel_remove_sync =
        (BassProcFn)GetProcAddress(g_bass_module, "BASS_ChannelRemoveSync");
    g_bass_sample_is_active =
        (BassProcFn)GetProcAddress(g_bass_module, "BASS_ChannelIsActive");

    unknown_04 = 0;
    unknown_08 = 0.0500000007f;
    music_stream_active = 0;

    if (g_bass_init(1, 44100, 0, hwnd, 0) == 0) {
        report_errorf("Can't initialize digital sound system");
        return 0;
    }

    g_bass_set_config(1, 50);
    g_active_music_stream = 0;
    g_active_music_stream_sync = 0;
    return 1;
}
