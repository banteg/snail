// Headless audio: the BASS-backed AudioBackend (cRBass) methods do nothing.
// Stage 4 plays samples, music and voice through miniaudio.

#include "audio_system.h"

int AudioBackend::stop_audio_backend() { return 0; }
void AudioBackend::stop_music_stream() {}
int AudioBackend::ensure_music_stream_from_path(char*, char) { return 1; }
char AudioBackend::prepare_music_stream_reload_if_path_changed(char*) { return 0; }
int AudioBackend::play_music_stream_from_bytes(char*, char*, int, char) { return 1; }
int AudioBackend::set_global_sample_volume_config(float) { return 0; }
int AudioBackend::set_global_stream_volume_config(float) { return 0; }
void AudioBackend::resume_audio_backend_if_paused() {}
char AudioBackend::pause_audio_backend_if_running() { return 0; }
int AudioBackend::load_registered_sound_sample_from_path(char*, int, int) { return 1; }
void AudioBackend::load_registered_sound_sample_from_bytes(char*, int, int, int) {}
void AudioBackend::play_registered_sound_sample_scaled(int, float) {}
void AudioBackend::play_registered_sound_sample_backend(int, float, float) {}
void AudioBackend::play_registered_sound_sample_scaled_panned(int, float, float, float) {}
int AudioBackend::stop_sound_sample_handle(int) { return 0; }
void AudioBackend::stop_registered_sound_sample(int) {}
bool AudioBackend::is_registered_sound_sample_playing(int) { return false; }
int AudioBackend::play_registered_sound_sample_default(int) { return 0; }
