// activate_all_borders @ 0x403300 (thiscall, ret)

#include "border_manager.h"

void BorderManager::activate_all_borders()
{
    for (int i = 0; i < BORDER_RECORD_COUNT; ++i) {
        int flags = borders[i].flags;
        if ((flags & FRONTEND_WIDGET_FLAG_DISABLED_BEFORE_DEACTIVATION) == 0) {
            flags &= ~FRONTEND_WIDGET_FLAG_DISABLED;
            borders[i].flags = flags;
        }
        borders[i].flags &=
            ~FRONTEND_WIDGET_FLAG_DISABLED_BEFORE_DEACTIVATION;
        borders[i].target_padding = borders[i].idle_padding;
        borders[i].active_padding = borders[i].idle_padding;
        borders[i].hover_blend_target = 0.0f;
    }
}
