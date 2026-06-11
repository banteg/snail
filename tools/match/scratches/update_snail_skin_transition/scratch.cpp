// update_snail_skin_transition @ 0x445f80 (thiscall, ret)
#include "snail_skin.h"

void SnailSkinTransition::update_snail_skin_transition()
{
    owner_render_state->model->flags |= 8;
    owner_render_state->model->material_index = slot_ids[selected_slot];
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
