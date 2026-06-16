// reset_voice_manager @ 0x448ec0 (thiscall, ret)

#include "voice_manager.h"

void VoiceManager::reset_voice_manager()
{
    global_progress = 0.0f;
    VoiceSet* set = sets;
    int count = 16;
    do {
        set->cooldown = 0.0f;
        ++set;
        --count;
    } while (count != 0);
}
