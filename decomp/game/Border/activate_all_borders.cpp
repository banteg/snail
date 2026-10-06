// activate_all_borders / cRBorderManager::ActivateBorders @ 0x403300

#include "border_manager.h"

void cRBorderManager::ActivateBorders()
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
