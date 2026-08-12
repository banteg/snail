// cRBorder::SetBelow @ 0x4027b0 (thiscall)

#include "frontend_widget.h"

void cRBorder::SetBelow(cRBorder* previous_widget)
{
    layout_anchor_x = previous_widget->layout_anchor_x;
    layout_anchor_y = previous_widget->layout_anchor_y + stack_gap + previous_widget->layout_height;
    layout_frontend_widget();
}
