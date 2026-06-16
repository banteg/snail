// set_frontend_widget_shortcut_key @ 0x402790 (thiscall, ret 0x4)

#include "frontend_widget.h"

int FrontendWidget::set_frontend_widget_shortcut_key(int shortcut_key_code_)
{
    shortcut_key_code = shortcut_key_code_;
    int result = widget_flags | 0x80000;
    widget_flags = result;
    return result;
}
