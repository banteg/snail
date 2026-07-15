// update_input_ok @ 0x4034d0 (thiscall)

#include "input_ok_state.h"

void InputOkState::update_input_ok()
{
    FrontendWidget* source = source_widget;
    unsigned int flags = source->input_flags;
    FrontendWidget* ok;
    float x;

    if ((flags & 4) != 0) {
        ok = ok_widget;
        x = ok->hot_padding;
        x = x + source->layout_width;
        x = x + source->layout_x;
        x = x + source->hot_padding;
    } else {
        if ((flags & 8) == 0)
            return;

        ok = ok_widget;
        x = source->layout_x - ok->layout_width - source->hot_padding
            - (ok->hot_padding + ok->hot_padding);
    }

    ok->layout_x = x;
    ok_widget->layout_y = source_widget->layout_y;
    ok_widget->layout_anchor_x = ok_widget->layout_x;
    source = source_widget;
    ok_widget->layout_anchor_y = source->layout_anchor_y;
}
