// Sound-effect manager call surface, partial. iOS names the same owner cRSound
// and the shared instance gRSound.
#ifndef SOUND_EFFECT_MANAGER_H
#define SOUND_EFFECT_MANAGER_H

struct Vector3;

class SoundEffectManager {
public:
    void play_sound_effect(int sound_id);
    void play_sound_effect_scaled(int sound_id, float gain);
    void play_sound_effect_at_position(int sound_id, Vector3& position);
    int play_warning_sample_backend(int sample_id);
    void stop_warning_sample_handle(int handle);
};

extern SoundEffectManager g_sound_effect_manager;

#endif
