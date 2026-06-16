// stack_widget_below @ 0x4027b0 (thiscall, ret 0x4)

#include "frontend_widget.h"

FrontendWidget* FrontendWidget::stack_widget_below(FrontendWidget* previous_widget)
{
    layout_anchor_x = previous_widget->layout_anchor_x;
    layout_anchor_y = previous_widget->layout_anchor_y + stack_gap + previous_widget->layout_height;
    return layout_frontend_widget();
}
