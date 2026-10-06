// initialize_bass_audio_backend @ 0x449460 (thiscall, ret 0x4)

#include "audio_system.h"

extern char* load_file_bytes(char* file_name, int* out_size);
extern int write_file_bytes(char* file_name, char* bytes, int byte_count);
extern void free_tracked_memory(void* ptr);
extern int report_errorf(char* format, ...);

extern "C" __declspec(dllimport) void* __stdcall LoadLibraryA(char* library_name);
extern "C" __declspec(dllimport) void* __stdcall GetProcAddress(void* module, char* name);

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
    g_bass_free = (BassFreeFn)GetProcAddress(g_bass_module, "BASS_Free");
    g_bass_update = (BassUpdateFn)GetProcAddress(g_bass_module, "BASS_Update");
    g_bass_stream_create_file =
        (BassStreamCreateFileFn)GetProcAddress(g_bass_module, "BASS_StreamCreateFile");
    g_bass_stream_play =
        (BassStreamPlayFn)GetProcAddress(g_bass_module, "BASS_StreamPlay");
    g_bass_stream_prebuf =
        (BassStreamPreBufFn)GetProcAddress(g_bass_module, "BASS_StreamPreBuf");
    g_bass_channel_stop =
        (BassChannelStopFn)GetProcAddress(g_bass_module, "BASS_ChannelStop");
    g_bass_stream_free =
        (BassStreamFreeFn)GetProcAddress(g_bass_module, "BASS_StreamFree");
    g_bass_sample_load =
        (BassSampleLoadFn)GetProcAddress(g_bass_module, "BASS_SampleLoad");
    g_bass_sample_play_ex =
        (BassSamplePlayExFn)GetProcAddress(g_bass_module, "BASS_SamplePlayEx");
    g_bass_sample_stop =
        (BassSampleStopFn)GetProcAddress(g_bass_module, "BASS_SampleStop");
    g_bass_set_config = (BassSetConfigFn)GetProcAddress(g_bass_module, "BASS_SetConfig");
    g_bass_stop = (BassStopFn)GetProcAddress(g_bass_module, "BASS_Stop");
    g_bass_start = (BassStartFn)GetProcAddress(g_bass_module, "BASS_Start");
    g_bass_pause = (BassPauseFn)GetProcAddress(g_bass_module, "BASS_Pause");
    g_bass_channel_bytes2_seconds =
        (BassChannelBytes2SecondsFn)GetProcAddress(
            g_bass_module, "BASS_ChannelBytes2Seconds");
    g_bass_channel_get_level =
        (BassChannelGetLevelFn)GetProcAddress(g_bass_module, "BASS_ChannelGetLevel");
    g_bass_channel_get_data =
        (BassChannelGetDataFn)GetProcAddress(g_bass_module, "BASS_ChannelGetData");
    g_bass_channel_set_sync =
        (BassChannelSetSyncFn)GetProcAddress(g_bass_module, "BASS_ChannelSetSync");
    g_bass_channel_get_position =
        (BassChannelGetPositionFn)GetProcAddress(
            g_bass_module, "BASS_ChannelGetPosition");
    g_bass_error_get_code =
        (BassErrorGetCodeFn)GetProcAddress(g_bass_module, "BASS_ErrorGetCode");
    g_bass_channel_remove_sync =
        (BassChannelRemoveSyncFn)GetProcAddress(
            g_bass_module, "BASS_ChannelRemoveSync");
    g_bass_channel_is_active =
        (BassChannelIsActiveFn)GetProcAddress(g_bass_module, "BASS_ChannelIsActive");

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
