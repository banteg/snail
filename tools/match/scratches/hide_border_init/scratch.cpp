// hide_border_init @ 0x4010e0 (thiscall, ret)

#include "frontend_widget.h"

int FrontendWidget::hide_border_init()
{
    int result = widget_flags;
    if ((result & 0x1000) != 0)
        return result;

    result |= 0x1000;
    hide_blend = 0.0f;
    widget_flags = result;
    return tooltip.reset_tooltip();
}
