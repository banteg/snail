// change_snail_skin @ 0x445fd0 (thiscall, ret 0x8)
#include "snail_skin.h"

void SnailSkin::change_snail_skin(int slot_id, float duration_seconds)
{
    active = 1;
    progress = 0.0f;
    if (duration_seconds == 0.0f) {
        progress_step = 0.0f;
        selected_slot = slot_id;
    } else {
        selected_slot = slot_id;
        progress_step = 1.0f / (duration_seconds * 60.0f);
    }
}
