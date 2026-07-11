// stop_warning_sample @ 0x446f60 (thiscall, ret; receiver unused)

#include "audio_system.h"
#include "warning.h"

void Warning::stop_warning_sample()
{
    int handle = g_sound_effect_manager.play_warning_sample_backend(0x32);
    g_sound_effect_manager.stop_warning_sample_handle(handle);
}
