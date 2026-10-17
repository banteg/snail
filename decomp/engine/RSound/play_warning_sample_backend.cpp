// cRSound::PlayLooped @ 0x44de20 (thiscall, ret 0x4)

#include "rshell.h"
#include "sound_effect_manager.h"

int cRSound::PlayLooped(int sample_id)
{
    return play_registered_warning_sample(sample_id);
}
