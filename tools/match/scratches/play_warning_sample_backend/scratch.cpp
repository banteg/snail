// play_warning_sample_backend @ 0x44de20 (SoundEffectManager thiscall, ret 0x4)

#include "sound_effect_manager.h"

int play_registered_warning_sample(int sample_id);

int SoundEffectManager::play_warning_sample_backend(int sample_id)
{
    return play_registered_warning_sample(sample_id);
}
