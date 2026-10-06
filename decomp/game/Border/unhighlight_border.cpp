// cRBorder::UnHighlight @ 0x4027e0 (thiscall)

#include "frontend_widget.h"

void cRBorder::UnHighlight()
{
    int result = *(int*)&idle_padding;
    hover_blend_target = 0.0f;
    *(int*)&target_padding = result;
}
