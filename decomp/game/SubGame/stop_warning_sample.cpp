// stop_warning_sample @ 0x446f60 (thiscall, ret; receiver unused)

#include "audio_system.h"
#include "warning.h"

void cRWarning::StopSample()
{
    int handle = g_sound_effect_manager.PlayLooped(0x32);
    g_sound_effect_manager.StopLooped(handle);
}
