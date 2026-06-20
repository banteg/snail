// Sound-effect manager call surface, partial.
#ifndef SOUND_EFFECT_MANAGER_H
#define SOUND_EFFECT_MANAGER_H

class SoundEffectManager {
public:
    void play_sound_effect(int sound_id);
    void play_sound_effect_scaled(int sound_id, float gain);
    int play_warning_sample_backend(int sample_id);
    void stop_warning_sample_handle(int handle);
};

extern SoundEffectManager g_sound_effect_manager;

#endif
