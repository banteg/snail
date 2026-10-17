// cRSound::PlayVolume @ 0x44de00 (thiscall, ret 8)

#include "rshell.h"
#include "sound_effect_manager.h"

void cRSound::PlayVolume(int sample_id, float gain)
{
    play_sound_effect_backend(sample_id, gain, -1.0f, 0.0f);
}
