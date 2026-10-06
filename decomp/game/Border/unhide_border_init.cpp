// cRBorder::UnHideInit @ 0x401110 (thiscall)

#include "frontend_widget.h"

void cRBorder::UnHideInit()
{
    int result = widget_flags;
    hide_blend = 1.0f;
    result &= ~FRONTEND_WIDGET_FLAG_HIDDEN;
    widget_flags = result;
}
