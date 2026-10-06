// update_slug_voice_manager @ 0x43f5e0 (thiscall, ret)

#include "slug_voice_manager.h"

void cRSlugVoiceManager::AI()
{
    if (progress > 0.0f) {
        float next_progress = step + progress;
        progress = next_progress;
        if (next_progress > 1.0f) {
            progress = 0.0f;
            active = 0;
        }
    }
}
