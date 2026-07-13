// border_sprite_extend @ 0x404540 (thiscall, ret 0x10)

#include "frontend_widget.h"

int FrontendWidget::border_sprite_extend(int sprite_a, int sprite_c, int sprite_b, char flag)
{
    sprite_hot_texture_id = sprite_a;
    sprite_hit_mask_texture_id = sprite_b;
    sprite_extend_texture_c = sprite_c;
    sprite_extend_enabled = 1;
    sprite_wobble_positive = flag;
    target_padding = 0.0f;
    idle_padding = 0.0f;
    hot_padding = 0.0f;
    return 0;
}
