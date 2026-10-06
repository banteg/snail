// cRSound::StopLooped @ 0x44de30 (thiscall, ret 0x4)

#include "sound_effect_manager.h"

void stop_registered_warning_sample(int handle);

void cRSound::StopLooped(int handle)
{
    stop_registered_warning_sample(handle);
}
