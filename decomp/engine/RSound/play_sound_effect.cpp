// cRSound::Play(int) @ 0x44dde0 (thiscall, ret 4)

#include "rshell.h"
#include "sound_effect_manager.h"

void cRSound::Play(int sample_id)
{
    play_sound_effect_backend(sample_id, 1.0f, -1.0f, 0.0f);
}
