// update_tooltip @ 0x403c20 (thiscall)

#include "sprite.h"
#include "tooltip_state.h"

extern char* g_game_base; // data_4df904
int report_errorf(char* format, ...);

class FrontendWidget {
public:
    int initialize_frontend_widget(unsigned int flags, char* text, int widget_type,
        float x, float y, Color4f* color, int alignment, float anchor_x);
    int layout_frontend_widget();

    char unknown_000[0x1a0];
    unsigned int widget_flags; // +0x1a0
    char unknown_1a4[0x214 - 0x1a4];
    float idle_padding; // +0x214
    float hot_padding; // +0x218
    float target_padding; // +0x21c
    float current_padding; // +0x220
    char unknown_224[0x238 - 0x224];
    float layout_left; // +0x238
    float layout_top; // +0x23c
    char unknown_240[0x248 - 0x240];
    float layout_width; // +0x248
    float layout_height; // +0x24c
    char unknown_250[0x25c - 0x250];
    int text_alignment; // +0x25c
    float anchor_x; // +0x260
    char unknown_264[0x26c - 0x264];
    float stack_gap; // +0x26c
    char unknown_270[0x6f4 - 0x270];
    float layout_anchor_x; // +0x6f4
    float layout_anchor_y; // +0x6f8
};

class BorderManager {
public:
    FrontendWidget* allocate_border();
    int kill_border(FrontendWidget* border);
};

void TooltipState::update_tooltip()
{
    int result;
    Color4f color;
    Color4f color_above;
    Color4f color_below;
    Color4f color_above_left;
    Color4f color_below_left;
    float progress;
    unsigned int flags;
    FrontendWidget* border;
    float right_edge;

    result = state;
    --result;
    if (result != 0) {
        --result;
        if (result != 0) {
            --result;
            if (result != 0)
                return;

            FrontendWidget* owner = owner_widget;
            if ((owner->widget_flags & 0x20000) == 0) {
                FrontendWidget* border = tooltip_widget;
                state = 1;
                ((BorderManager*)(g_game_base + 0xb4c))->kill_border(border);
                tooltip_widget = 0;
            }
            return;
        }

        FrontendWidget* owner = owner_widget;
        if ((owner->widget_flags & 0x20000) == 0)
            goto reset_tooltip_state;

        progress = delay_step + delay_progress;
        delay_progress = progress;
        if (progress <= 1.0f)
            return;

        float anchor;
        if (owner->text_alignment != 0)
            anchor = owner->anchor_x;
        else
            anchor = owner->layout_width * 0.5f + owner->layout_anchor_x - 320.0f;

        state = 3;
        if (tooltip_widget != 0)
            report_errorf("Tool tip overload");
        else
            tooltip_widget = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();

        flags = mode_flags;
        if ((flags & 1) != 0) {
            tooltip_widget->initialize_frontend_widget(2, (char*)this, 7,
                *(float*)(g_game_base + 0x29c), *(float*)(g_game_base + 0x2a0) + 64.0f,
                color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 1, anchor);
        } else if ((flags & 4) != 0) {
            FrontendWidget* local_owner = owner_widget;
            tooltip_widget->initialize_frontend_widget(2, (char*)this, 7,
                local_owner->layout_anchor_x,
                local_owner->layout_anchor_y - local_owner->current_padding,
                color_above.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 1, anchor);
            FrontendWidget* border = tooltip_widget;
            border->layout_anchor_y =
                border->layout_anchor_y - (border->layout_height + border->current_padding);
        } else if ((flags & 2) != 0) {
            FrontendWidget* local_owner = owner_widget;
            tooltip_widget->initialize_frontend_widget(2, (char*)this, 7,
                local_owner->layout_anchor_x,
                local_owner->layout_anchor_y + local_owner->layout_height +
                    local_owner->current_padding,
                color_below.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 1, anchor);
            FrontendWidget* border = tooltip_widget;
            border->layout_anchor_y = border->layout_anchor_y + border->current_padding;
        } else if ((flags & 0x10) != 0) {
            FrontendWidget* local_owner = owner_widget;
            tooltip_widget->initialize_frontend_widget(2, (char*)this, 7,
                local_owner->layout_anchor_x,
                local_owner->layout_anchor_y - local_owner->current_padding,
                color_above_left.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 0, 0.0f);
            FrontendWidget* border = tooltip_widget;
            border->layout_anchor_y =
                border->layout_anchor_y - (border->layout_height + border->current_padding);
        } else if ((flags & 8) != 0) {
            FrontendWidget* local_owner = owner_widget;
            tooltip_widget->initialize_frontend_widget(2, (char*)this, 7,
                local_owner->layout_anchor_x,
                local_owner->layout_anchor_y + local_owner->layout_height +
                    local_owner->current_padding,
                color_below_left.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 0, 0.0f);
            FrontendWidget* border = tooltip_widget;
            border->layout_anchor_y = border->layout_anchor_y + border->current_padding;
        }

        border = tooltip_widget;
        if (border->layout_left - border->hot_padding - border->stack_gap < 0.0f)
            border->layout_anchor_x = border->stack_gap;

        border = tooltip_widget;
        right_edge = border->stack_gap + border->layout_width + border->layout_left + border->hot_padding;
        if (right_edge > 640.0f)
            border->layout_anchor_x = border->layout_anchor_x - (right_edge - 640.0f);
        tooltip_widget->layout_frontend_widget();
        return;

reset_tooltip_state:
        state = 1;
        return;
    }

    result = (int)owner_widget;
    if ((owner_widget->widget_flags & 0x20000) != 0) {
        delay_progress = 0.0f;
        state = 2;
    }

    return;
}
