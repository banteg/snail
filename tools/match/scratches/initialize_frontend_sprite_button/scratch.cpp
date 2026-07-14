// initialize_frontend_sprite_button @ 0x401a70 (thiscall, ret 0x1c)

#include "border_manager.h"
#include "frontend_widget.h"
#include "game_root.h"

extern GameRoot* g_game; // data_4df904
int report_errorf(char* format, ...);

void FrontendWidget::initialize_frontend_sprite_button(
    int flags,
    int sprite,
    float x,
    float y,
    tColour* color,
    float anchor_x,
    int layer)
{
    char* self = (char*)this;
    FrontendWidget* head = (FrontendWidget*)&g_game->border_manager;

    if ((list_flags & 0x200) != 0) {
        report_errorf("List ADDafter");
    } else {
        list_prev = head;
        list_next = head->list_next;
        head->list_next = this;
        BodNode* next = list_next;
        if (next != 0)
            next->list_prev = this;
        list_flags |= 0x200;
    }

    border_texture_id = 5;
    texture_hit_test_enabled = 0;
    tooltip.state = 0;
    tooltip.owner_widget = this;
    tooltip.tooltip_widget = 0;
    tooltip.owner_widget_38 = this;
    render_inset_delta = 0.0f;
    render_inset_base = 20.0f;
    render_inset_dynamic = 0;
    sprite_shadow_offset = 4.0f;
    font_id = 0;
    tColour* idle_fill = &idle_fill_color;
    font_scale = 1.0f;
    idle_padding = 10.0f;
    hot_padding = 15.0f;
    stack_gap = 20.0f;
    border_edge = 0.0f;
    *(int*)(self + 0x38) = 1;
    unhide_border_init();

    int widget_flags = flags | 0x40801;
    this->widget_flags = widget_flags;
    previous_widget_flags = widget_flags;
    text_buffer[0] = 0;
    layout_anchor_x = x;
    layout_anchor_y = y;

    *idle_fill = *color;
    hot_fill_color = *color;

    tColour white;
    idle_text_color = *white.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
    hot_text_color = *white.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);

    if (((unsigned char)this->widget_flags & 2) != 0) {
        hover_blend_target = 1.0f;
        target_padding = hot_padding;
    } else {
        hover_blend_target = 0.0f;
        target_padding = idle_padding;
    }

    hover_blend_current = hover_blend_target;
    current_padding = target_padding;
    text_effect_target = 0.0f;
    text_effect_current = 0.0f;
    layout_mode = 0;
    this->anchor_x = anchor_x;
    float adjusted_anchor_x =
        anchor_x + g_game->border_manager.justify_centre;
    layout_x = x;
    layout_y = y;
    this->anchor_x = adjusted_anchor_x;

    layout_width = (float)g_sprite_texture_table[sprite]->loaded_width;
    layout_height = (float)g_sprite_texture_table[sprite]->loaded_height;
    texture_hit_width = layout_width;
    texture_hit_height = layout_height;
    layout_anchor_x = x;
    texture_id = sprite;
    layout_anchor_y = y;
    texture_layer = layer;
    teardown_progress = 0.0f;
    teardown_progress_step = 0.0f;
    layout_frontend_widget();
}
