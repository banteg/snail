// Audio backend and sound-effect call surfaces, partial.
#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

#include "sound_effect_manager.h"

// The native exhaustion diagnostic names this original RShell.h capacity.
enum {
    RSHELL_SOUND_MAX = 256,
};

/*
 * Exact BASS 2.0 dispatch surface resolved by initialize_bass_audio_backend.
 * These signatures follow the bundled bass20 SDK header; keeping them here
 * prevents exact audio scratches from drifting into incompatible local
 * function-pointer declarations.
 */
typedef unsigned int BassHandle;
typedef unsigned __int64 BassQword;
typedef void (__stdcall* BassSyncProc)(
    BassHandle sync_handle, BassHandle channel, unsigned int data, unsigned int user);
typedef unsigned int (__stdcall* BassSetConfigFn)(unsigned int option, unsigned int value);
typedef unsigned int (__stdcall* BassErrorGetCodeFn)();
typedef int (__stdcall* BassInitFn)(
    unsigned int device,
    unsigned int frequency,
    unsigned int flags,
    void* hwnd,
    const void* direct_sound_guid);
typedef int (__stdcall* BassFreeFn)();
typedef int (__stdcall* BassUpdateFn)();
typedef int (__stdcall* BassStartFn)();
typedef int (__stdcall* BassStopFn)();
typedef int (__stdcall* BassPauseFn)();
typedef BassHandle (__stdcall* BassSampleLoadFn)(
    int from_memory,
    const void* path_or_bytes,
    unsigned int offset,
    unsigned int byte_count,
    unsigned int max_instances,
    unsigned int flags);
typedef BassHandle (__stdcall* BassSamplePlayExFn)(
    BassHandle sample_handle,
    unsigned int start,
    int frequency,
    int volume,
    int pan,
    int loop);
typedef int (__stdcall* BassSampleStopFn)(BassHandle sample_handle);
typedef BassHandle (__stdcall* BassStreamCreateFileFn)(
    int from_memory,
    const void* path_or_bytes,
    unsigned int offset,
    unsigned int byte_count,
    unsigned int flags);
typedef void (__stdcall* BassStreamFreeFn)(BassHandle stream_handle);
typedef int (__stdcall* BassStreamPreBufFn)(BassHandle stream_handle);
typedef int (__stdcall* BassStreamPlayFn)(
    BassHandle stream_handle, int flush, unsigned int flags);
typedef float (__stdcall* BassChannelBytes2SecondsFn)(
    BassHandle channel_handle, BassQword position);
typedef unsigned int (__stdcall* BassChannelIsActiveFn)(BassHandle channel_handle);
typedef int (__stdcall* BassChannelStopFn)(BassHandle channel_handle);
typedef BassQword (__stdcall* BassChannelGetPositionFn)(BassHandle channel_handle);
typedef unsigned int (__stdcall* BassChannelGetLevelFn)(BassHandle channel_handle);
typedef unsigned int (__stdcall* BassChannelGetDataFn)(
    BassHandle channel_handle, void* buffer, unsigned int byte_count);
typedef BassHandle (__stdcall* BassChannelSetSyncFn)(
    BassHandle channel_handle,
    unsigned int sync_type,
    BassQword parameter,
    BassSyncProc callback,
    unsigned int user);
typedef int (__stdcall* BassChannelRemoveSyncFn)(
    BassHandle channel_handle, BassHandle sync_handle);

class AudioBackend {
public:
    char initialize_bass_audio_backend(void* hwnd); // @ 0x449460
    void uninitialize_bass_audio_backend(); // @ 0x4496d0
    void noop_runtime_ai();
    int stop_audio_backend(); // @ 0x449b90
    void stop_music_stream(); // @ 0x4498d0
    int ensure_music_stream_from_path(char* path, char play_mode); // @ 0x449720
    char prepare_music_stream_reload_if_path_changed(char* path); // @ 0x4497e0
    int play_music_stream_from_bytes(
        char* path, char* bytes, int byte_count, char play_mode); // @ 0x449820
    int set_global_sample_volume_config(float volume); // @ 0x449b50
    int set_global_stream_volume_config(float volume); // @ 0x449b70
    void resume_audio_backend_if_paused(); // @ 0x449ba0
    char pause_audio_backend_if_running(); // @ 0x449bc0
    void set_audio_normalization_scales(
        float music_scale, float sfx_scale, float voice_scale); // @ 0x449be0
    int load_registered_sound_sample_from_path(
        char* path, int sample_id, int normalization_class); // @ 0x449920
    void load_registered_sound_sample_from_bytes(
        char* bytes, int byte_count, int sample_id, int normalization_class); // @ 0x449960

    // Gameplay callsites spell these helpers as calls on the backend object.
    void play_registered_sound_sample_scaled(int sample_id, float volume); // @ 0x4499a0
    void play_registered_sound_sample_backend(
        int sample_id, float volume, float pitch); // @ 0x449a80
    void play_registered_sound_sample_scaled_panned(
        int sample_id, float volume, float pitch, float pan); // @ 0x449ae0
    int stop_sound_sample_handle(int sample_handle); // @ 0x449a10
    void stop_registered_sound_sample(int sample_id); // @ 0x449a20
    bool is_registered_sound_sample_playing(int sample_id); // @ 0x449a40
    int play_registered_sound_sample_default(int sample_id); // @ 0x449a60

    unsigned char music_stream_active; // +0x00
    char unknown_01[0x04 - 0x01];
    int unknown_04; // +0x04, cleared during backend initialization
    float unknown_08; // +0x08, initialized to 0.05f
    float music_normalization_scale; // +0x0c
    float sfx_normalization_scale;   // +0x10
    float voice_normalization_scale; // +0x14
    unsigned char is_paused;         // +0x18
};

extern AudioBackend g_audio_backend; // 0x753c58
extern char g_cached_music_path[0x100]; // data_7516a0
extern char g_registered_sound_sample_names[RSHELL_SOUND_MAX][0x80]; // data_5088b0
extern int g_registered_sound_sample_count; // data_5108b0
extern int g_registered_sound_sample_handles[RSHELL_SOUND_MAX]; // data_7537e0
extern float g_stream_volume_scale; // g_audio_backend + 0x0c
extern float g_audio_backend_sfx_normalization_scale; // g_audio_backend + 0x10
extern float g_audio_backend_voice_normalization_scale; // g_audio_backend + 0x14

extern BassChannelBytes2SecondsFn g_bass_channel_bytes2_seconds; // 0x75162c
extern BassChannelRemoveSyncFn g_bass_channel_remove_sync; // 0x75165c
extern BassStartFn g_bass_start; // 0x751660
extern BassStreamPreBufFn g_bass_stream_prebuf; // 0x751670
extern BassErrorGetCodeFn g_bass_error_get_code; // 0x751674
extern BassHandle g_active_music_stream_sync; // 0x751680
extern BassUpdateFn g_bass_update; // 0x751698
extern BassStreamPlayFn g_bass_stream_play; // 0x7517a0
extern BassSamplePlayExFn g_bass_sample_play_ex; // 0x7527b4
extern BassSampleLoadFn g_bass_sample_load; // 0x7537cc
extern BassFreeFn g_bass_free; // 0x7537d8
extern BassChannelStopFn g_bass_channel_stop; // 0x753be4
extern BassStreamCreateFileFn g_bass_stream_create_file; // 0x753bf8
extern BassStopFn g_bass_stop; // 0x753bfc
extern BassInitFn g_bass_init; // 0x753c08
extern BassChannelGetDataFn g_bass_channel_get_data; // 0x753c18
extern BassSetConfigFn g_bass_set_config; // 0x753c1c
extern BassHandle g_active_music_stream; // 0x753c20
extern void* g_bass_module; // 0x753c90
extern BassSampleStopFn g_bass_sample_stop; // 0x753c94
extern BassChannelGetPositionFn g_bass_channel_get_position; // 0x753c98
extern BassChannelIsActiveFn g_bass_channel_is_active; // 0x753ca8
extern BassStreamFreeFn g_bass_stream_free; // 0x753cb0
extern BassChannelGetLevelFn g_bass_channel_get_level; // 0x753cbc
extern BassPauseFn g_bass_pause; // 0x753cc0
extern BassChannelSetSyncFn g_bass_channel_set_sync; // 0x753cc4

#endif
