// update_slug_voice_ai @ 0x43f520 (thiscall, ret)

#include "slug_hazard_types.h"

void Slug::update_slug_voice_ai()
{
    if (voice_active != 0) {
        float next_progress = voice_progress_step + voice_progress;
        voice_progress = next_progress;
        if (next_progress > 1.0f) {
            voice_progress = 0.0f;
            voice_active = 0;
        }
    }
}
