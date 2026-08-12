// queue_frontend_widget_flag_after_delay @ 0x403f60 (thiscall, ret 0x8)

#include "border_manager.h"
#include "game_root.h"


void cRBorderManager::queue_frontend_widget_flag_after_delay(
    cRBorder* widget, int queued_flags)
{
    if (delayed_widget_active == 0) {
        if ((widget->widget_flags & FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION) != 0)
            g_game->fade.Start(0);
        delayed_widget = widget;
        delayed_widget_active = 1;
        delayed_widget_progress = 0.0f;
        delayed_widget_progress_step = 0.0833333358f;
        delayed_widget_flags = queued_flags;
    }
}
