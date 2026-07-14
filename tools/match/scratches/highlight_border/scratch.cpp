// highlight_border @ 0x402800 (thiscall, ret)

#include "frontend_widget.h"

void FrontendWidget::highlight_border()
{
    int result = *(int*)&hot_padding;
    hover_blend_target = 1.0f;
    *(int*)&target_padding = result;
}
