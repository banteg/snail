// cRBorder::Highlight @ 0x402800 (thiscall)

#include "frontend_widget.h"

void cRBorder::Highlight()
{
    int result = *(int*)&hot_padding;
    hover_blend_target = 1.0f;
    *(int*)&target_padding = result;
}
