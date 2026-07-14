// initialize_frontend_widget @ 0x401d30 (thiscall, ret 0x20)

#include "border_manager.h"
#include "frontend_widget.h"
#include "game_root.h"

extern GameRoot* g_game; // data_4df904
extern char g_blank_text[]; // data_4dfb08

int report_errorf(char* format, ...);
void __cdecl rstrcpy_checked_ascii(char* destination, char* source);

void FrontendWidget::initialize_frontend_widget(
    int flags,
    char* text,
    int widget_type,
    float x,
    float y,
    tColour* color,
    int alignment,
    float anchor_x)
{
    char* self = (char*)this;
    FrontendWidget* head;
    tColour tmp0;
    tColour tmp1;
    tColour tmp2;
    tColour tmp3;
    tColour tmp4;
    tColour tmp5;
    tColour tmp6;
    tColour tmp7;
    tColour tmp8;
    tColour tmp9;
    tColour tmp10;
    tColour tmp11;
    tColour tmp12;
    tColour tmp13;
    tColour tmp14;
    tColour tmp15;

    this->widget_type = widget_type;
    border_texture_id = 5;
    texture_hit_test_enabled = 0;
    render_inset_delta = 0.0f;
    render_inset_base = 20.0f;
    render_inset_dynamic = 0;
    head = (FrontendWidget*)&g_game->border_manager;

    if ((list_flags & 0x200) != 0) {
        report_errorf("List ADDafter");
    } else {
        list_prev = head;
        list_next = head->list_next;
        head->list_next = this;
        if (list_next != 0)
            list_next->list_prev = this;
        list_flags |= 0x200;
    }

    tooltip.state = 0;
    tooltip.owner_widget = this;
    tooltip.tooltip_widget = 0;
    tooltip.owner_widget_38 = this;
    widget_flags = flags | 0x40001;

    hot_text_color.set_color_white();
    hot_fill_color.set_color_white();

    switch (widget_type) {
    case 20:
        font_id = 0;
        font_scale = 1.3f;
        idle_padding = 9.0f;
        hot_padding = 13.0f;
        stack_gap = 26.0f;
        idle_text_color = *tmp0.set_color_rgba(1.0f, 0.52156866f, 0.0f, 0.69999999f);
        hot_text_color = *tmp1.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
        idle_fill_color = *tmp2.set_color_rgba(0.32941177f, 0.22352941f, 0.50196081f, 0.69999999f);
        hot_fill_color = *tmp3.set_color_rgba(0.60784316f, 0.30980393f, 0.69411767f, 1.0f);
        break;
    case 22:
        render_inset_base = 20.0f;
        font_id = 0;
        font_scale = 0.64999998f;
        idle_padding = 1.0f;
        hot_padding = 3.0f;
        stack_gap = 2.0f;
        render_inset_dynamic = 1;
        idle_text_color = *tmp4.set_color_rgba(1.0f, 0.52156866f, 0.0f, 0.69999999f);
        hot_text_color = *tmp5.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
        idle_fill_color = *tmp6.set_color_rgba(0.32941177f, 0.22352941f, 0.50196081f, 0.69999999f);
        hot_fill_color = *tmp7.set_color_rgba(0.60784316f, 0.30980393f, 0.69411767f, 1.0f);
        break;
    case 23:
        font_id = 0;
        font_scale = 1.14f;
        idle_padding = 6.0f;
        hot_padding = 7.0f;
        stack_gap = 2.0f;
        render_inset_base = 20.0f;
        idle_text_color = *tmp8.set_color_rgba(1.0f, 0.52156866f, 0.0f, 0.69999999f);
        hot_text_color = *tmp9.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
        idle_fill_color = *tmp10.set_color_rgba(0.32941177f, 0.22352941f, 0.50196081f, 0.69999999f);
        hot_fill_color = *tmp11.set_color_rgba(0.60784316f, 0.30980393f, 0.69411767f, 1.0f);
        break;
    case 21:
        font_id = 0;
        font_scale = 1.0f;
        idle_padding = 9.0f;
        hot_padding = 13.0f;
        stack_gap = 26.0f;
        idle_text_color = *tmp12.set_color_rgba(1.0f, 0.52156866f, 0.0f, 0.69999999f);
        hot_text_color = *tmp13.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
        idle_fill_color = *tmp14.set_color_rgba(0.32941177f, 0.22352941f, 0.50196081f, 0.69999999f);
        hot_fill_color = *tmp15.set_color_rgba(0.60784316f, 0.30980393f, 0.69411767f, 1.0f);
        break;
    default:
        report_errorf("Unknown Border Style Requested");
        break;
    }

    slider_position_target = 0.5f;
    slider_position_current = 0.5f;
    *(int*)(self + 0x38) = 1;
    unhide_border_init();
    rstrcpy_checked_ascii(text_buffer, text);
    layout_anchor_x = x;
    layout_anchor_y = y;
    hover_blend_target = 1.0f;

    if (((unsigned char)widget_flags & 2) != 0)
        highlight_border();
    else
        unhighlight_border();

    hover_blend_current = hover_blend_target;
    current_padding = target_padding = idle_padding;
    text_effect_target = 0.0f;
    text_effect_current = 0.0f;
    text_alignment = alignment;
    this->anchor_x = anchor_x;
    this->anchor_x =
        anchor_x + g_game->border_manager.justify_centre;
    mouse_history_warmup_frames = 1;

    if ((widget_flags & 0x100000) != 0) {
        slider_more_widget = g_game->border_manager.allocate_border();
        float slider_y = y + 40.0f;
        slider_more_widget->initialize_frontend_sprite_button(
            (widget_flags & 0x800000) | 0x20400814,
            42,
            g_game->border_manager.justify_centre + 458.0f,
            slider_y,
            tmp0.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0.0f,
            4);
        slider_more_widget->border_sprite_extend(44, 43, 45, 1);

        slider_less_widget = g_game->border_manager.allocate_border();
        slider_less_widget->initialize_frontend_sprite_button(
            (widget_flags & 0x800000) | 0x20400814,
            38,
            g_game->border_manager.justify_centre + 118.0f,
            slider_y,
            tmp0.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0.0f,
            4);
        slider_less_widget->border_sprite_extend(40, 39, 41, 0);

        slider_value_widget = g_game->border_manager.allocate_border();
        slider_value_widget->initialize_frontend_widget(
            0x400000,
            (char*)"00%",
            21,
            0.0f,
            layout_anchor_y + 40.0f,
            tmp0.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            0.0f);
    }

    layout_frontend_widget();
}
