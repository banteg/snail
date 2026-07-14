// unhighlight_border @ 0x4027e0 (thiscall, ret)

#include "frontend_widget.h"

void FrontendWidget::unhighlight_border()
{
    int result = *(int*)&idle_padding;
    hover_blend_target = 0.0f;
    *(int*)&target_padding = result;
}
