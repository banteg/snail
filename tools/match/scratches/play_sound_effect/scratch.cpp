// play_sound_effect @ 0x44dde0 (thiscall, ret 4)

#include "sound_effect_manager.h"

void play_sound_effect_backend(int sample_id, float gain, float pitch, float pan);

void SoundEffectManager::play_sound_effect(int sample_id)
{
    play_sound_effect_backend(sample_id, 1.0f, -1.0f, 0.0f);
}
