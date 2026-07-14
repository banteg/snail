// play_sound_effect_scaled @ 0x44de00 (thiscall, ret 8)

#include "sound_effect_manager.h"

void play_sound_effect_backend(int sample_id, float gain, float pitch, float pan);

void SoundEffectManager::play_sound_effect_scaled(int sample_id, float gain)
{
    play_sound_effect_backend(sample_id, gain, -1.0f, 0.0f);
}
