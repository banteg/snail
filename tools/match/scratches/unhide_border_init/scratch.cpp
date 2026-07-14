// unhide_border_init @ 0x401110 (thiscall, ret)

#include "frontend_widget.h"

void FrontendWidget::unhide_border_init()
{
    int result = widget_flags;
    hide_blend = 1.0f;
    result &= ~FRONTEND_WIDGET_FLAG_HIDDEN;
    widget_flags = result;
}
