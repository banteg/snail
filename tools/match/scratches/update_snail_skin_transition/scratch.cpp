// update_snail_skin_transition @ 0x445f80 (thiscall, ret)
#include "player.h"

void SnailSkin::update_snail_skin_transition()
{
    owner_snail->visual_root->flags |= 8;
    owner_snail->visual_root->material_index = slot_ids[selected_slot];
    switch (active) {
    case 1:
        progress = progress_step + progress;
        if (progress > 1.0f) {
            progress = 0.0f;
            active = 0;
            selected_slot = 0;
        }
        break;
    }
}
