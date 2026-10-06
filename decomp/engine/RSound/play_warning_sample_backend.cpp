// cRSound::PlayLooped @ 0x44de20 (thiscall, ret 0x4)

#include "sound_effect_manager.h"

int play_registered_warning_sample(int sample_id);

int cRSound::PlayLooped(int sample_id)
{
    return play_registered_warning_sample(sample_id);
}
