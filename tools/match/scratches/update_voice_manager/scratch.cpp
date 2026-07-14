// update_voice_manager @ 0x4492a0 (thiscall, ret)

#include "voice_manager.h"

void VoiceManager::update_voice_manager()
{
    VoiceSet* set = sets;
    int count = VOICE_SET_COUNT;
    do {
        set->update_voice_set();
        ++set;
        --count;
    } while (count != 0);
    global_progress = global_progress + 0.016666668f;
}
