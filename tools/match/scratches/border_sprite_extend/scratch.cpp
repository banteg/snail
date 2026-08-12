// border_sprite_extend @ 0x404540 (thiscall, ret 0x10)

#include "frontend_widget.h"

void cRBorder::border_sprite_extend(
    int hot_texture_id,
    int retained_state,
    int hit_mask_texture_id,
    char wobble_positive)
{
    sprite_hot_texture_id = hot_texture_id;
    sprite_hit_mask_texture_id = hit_mask_texture_id;
    sprite_extend_retained_state = retained_state;
    sprite_extend_enabled = 1;
    sprite_wobble_positive = wobble_positive;
    target_padding = 0.0f;
    idle_padding = 0.0f;
    hot_padding = 0.0f;
}
