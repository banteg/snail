// Audio backend and sound-effect call surfaces, partial.
#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

#include "sound_effect_manager.h"

class AudioBackend {
public:
    char initialize_bass_audio_backend(void* hwnd); // @ 0x449460
    void noop_runtime_ai();
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
    int load_registered_sound_sample_from_bytes(
        char* bytes, int byte_count, int sample_id, int normalization_class); // @ 0x449960

    // Gameplay callsites spell these helpers as calls on the backend object.
    void play_registered_sound_sample_scaled(int sample_id, float volume); // @ 0x4499a0
    void play_registered_sound_sample_backend(
        int sample_id, float volume, float pitch); // @ 0x449a80
    void play_registered_sound_sample_scaled_panned(
        int sample_id, float volume, float pitch, float pan); // @ 0x449ae0
    void stop_registered_sound_sample(int sample_id); // @ 0x449a20
    bool is_registered_sound_sample_playing(int sample_id); // @ 0x449a40

    unsigned char music_stream_active; // +0x00
    char unknown_01[0x0c - 0x01];
    float music_normalization_scale; // +0x0c
    float sfx_normalization_scale;   // +0x10
    float voice_normalization_scale; // +0x14
    unsigned char is_paused;         // +0x18
};

extern AudioBackend g_audio_backend; // 0x753c58

#endif
