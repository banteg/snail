// update_voice_set @ 0x449360 (thiscall, ret)

#include "voice_manager.h"

void VoiceSet::update_voice_set()
{
    if (cooldown > 0.0f) {
        float next_progress = cooldown_step + cooldown;
        cooldown = next_progress;
        if (next_progress > 1.0f) {
            cooldown = 0.0f;
        }
    }
}
