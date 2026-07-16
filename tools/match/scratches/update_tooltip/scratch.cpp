// update_tooltip @ 0x403c20 (thiscall)

#include "frontend_widget.h"
#include "game_root.h"

int report_errorf(char* format, ...);

void FrontendWidgetTooltip::update_tooltip()
{
    tColour color;
    tColour color_above;
    tColour color_below;
    tColour color_above_left;
    tColour color_below_left;
    float progress;
    unsigned int flags;
    FrontendWidget* border;
    float right_edge;

    switch (state) {
    case 3: {
        FrontendWidget* owner = owner_widget;
        if ((owner->widget_flags & FRONTEND_WIDGET_FLAG_POINTER_INSIDE) == 0) {
            FrontendWidget* border = tooltip_widget;
            state = 1;
            g_game->border_manager.kill_border(border);
            tooltip_widget = 0;
        }
        return;
    }

    case 2: {
        FrontendWidget* owner = owner_widget;
        if ((owner->widget_flags & FRONTEND_WIDGET_FLAG_POINTER_INSIDE) != 0) {
            progress = delay_step + delay_progress;
            delay_progress = progress;
            if (progress <= 1.0f)
                return;

            float anchor;
            if (owner->layout_mode != 0)
                anchor = owner->layout_center_x;
            else
                anchor = owner->layout_width * 0.5f + owner->layout_anchor_x - 320.0f;

            state = 3;
            if (tooltip_widget != 0)
                report_errorf("Tool tip overload");
            else
                tooltip_widget = g_game->border_manager.allocate_border();

            flags = mode_flags;
            if ((flags & 1) != 0) {
                tooltip_widget->initialize_frontend_widget(
                    FRONTEND_WIDGET_FLAG_HIGHLIGHTED, (char*)this, 7,
                    g_game->players[0].mouse_cursor.saved_x,
                    g_game->players[0].mouse_cursor.saved_y + 64.0f,
                    color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 1, anchor);
            } else if ((flags & 4) != 0) {
                FrontendWidget* local_owner = owner_widget;
                tooltip_widget->initialize_frontend_widget(
                    FRONTEND_WIDGET_FLAG_HIGHLIGHTED, (char*)this, 7,
                    local_owner->layout_anchor_x,
                    local_owner->layout_anchor_y - local_owner->active_padding,
                    color_above.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 1, anchor);
                FrontendWidget* border = tooltip_widget;
                border->layout_anchor_y =
                    border->layout_anchor_y - (border->layout_height + border->active_padding);
            } else if ((flags & 2) != 0) {
                FrontendWidget* local_owner = owner_widget;
                tooltip_widget->initialize_frontend_widget(
                    FRONTEND_WIDGET_FLAG_HIGHLIGHTED, (char*)this, 7,
                    local_owner->layout_anchor_x,
                    local_owner->layout_anchor_y + local_owner->layout_height +
                        local_owner->active_padding,
                    color_below.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 1, anchor);
                FrontendWidget* border = tooltip_widget;
                border->layout_anchor_y = border->layout_anchor_y + border->active_padding;
            } else if ((flags & 0x10) != 0) {
                FrontendWidget* local_owner = owner_widget;
                tooltip_widget->initialize_frontend_widget(
                    FRONTEND_WIDGET_FLAG_HIGHLIGHTED, (char*)this, 7,
                    local_owner->layout_anchor_x,
                    local_owner->layout_anchor_y - local_owner->active_padding,
                    color_above_left.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 0, 0.0f);
                FrontendWidget* border = tooltip_widget;
                border->layout_anchor_y =
                    border->layout_anchor_y - (border->layout_height + border->active_padding);
            } else if ((flags & 8) != 0) {
                FrontendWidget* local_owner = owner_widget;
                tooltip_widget->initialize_frontend_widget(
                    FRONTEND_WIDGET_FLAG_HIGHLIGHTED, (char*)this, 7,
                    local_owner->layout_anchor_x,
                    local_owner->layout_anchor_y + local_owner->layout_height +
                        local_owner->active_padding,
                    color_below_left.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 0, 0.0f);
                FrontendWidget* border = tooltip_widget;
                border->layout_anchor_y = border->layout_anchor_y + border->active_padding;
            }

            border = tooltip_widget;
            if (border->layout_x - border->hot_padding - border->stack_gap < 0.0f)
                border->layout_anchor_x = border->stack_gap;

            border = tooltip_widget;
            right_edge =
                border->stack_gap + border->layout_width + border->layout_x + border->hot_padding;
            if (right_edge > 640.0f)
                border->layout_anchor_x = border->layout_anchor_x - (right_edge - 640.0f);
            tooltip_widget->layout_frontend_widget();
            return;
        }

        state = 1;
        return;
    }

    case 1: {
        FrontendWidget* owner = owner_widget;
        if ((owner->widget_flags & FRONTEND_WIDGET_FLAG_POINTER_INSIDE) != 0) {
            delay_progress = 0.0f;
            state = 2;
        }

        return;
    }

    default:
        return;
    }
}
