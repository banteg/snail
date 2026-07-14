// update_snail_skin_transition @ 0x445f80 (thiscall, ret)
#include "object_render_types.h"
#include "player.h"

void SnailSkin::update_snail_skin_transition()
{
    owner_snail->object->flags |= OBJECT_FLAG_USE_OVERRIDE_TEXTURE;
    owner_snail->object->override_texture_ref = material_overrides[selected_slot];
    switch (active) {
    case 1:
        progress = progress_step + progress;
        if (progress > 1.0f) {
            progress = 0.0f;
            active = 0;
            selected_slot = SNAIL_SKIN_SLOT_DEFAULT;
        }
        break;
    }
}
