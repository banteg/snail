// cRBorder::SetKeyLeft @ 0x402790 (thiscall)

#include "frontend_widget.h"

void cRBorder::SetKeyLeft(int shortcut_key_code_)
{
    shortcut_key_code = shortcut_key_code_;
    int result = widget_flags | FRONTEND_WIDGET_FLAG_SHORTCUT_KEY_ENABLED;
    widget_flags = result;
}
