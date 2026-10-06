// cRBorder::HideInit @ 0x4010e0 (thiscall)

#include "frontend_widget.h"

void cRBorder::HideInit()
{
    int result = widget_flags;
    if ((result & FRONTEND_WIDGET_FLAG_HIDDEN) != 0)
        return;

    result |= FRONTEND_WIDGET_FLAG_HIDDEN;
    hide_blend = 0.0f;
    widget_flags = result;
    tooltip.ReSet();
}
