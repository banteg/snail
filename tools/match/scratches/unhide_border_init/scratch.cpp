// unhide_border_init @ 0x401110 (thiscall, ret)

#include "frontend_widget.h"

void FrontendWidget::unhide_border_init()
{
    int result = widget_flags;
    hide_blend = 1.0f;
    result &= ~0x1000;
    widget_flags = result;
}
