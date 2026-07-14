// stop_warning_sample_handle @ 0x44de30 (SoundEffectManager thiscall, ret 0x4)

#include "sound_effect_manager.h"

void stop_registered_warning_sample(int handle);

void SoundEffectManager::stop_warning_sample_handle(int handle)
{
    stop_registered_warning_sample(handle);
}
