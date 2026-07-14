// queue_frontend_widget_flag_after_delay @ 0x403f60 (thiscall, ret 0x8)

#include "border_manager.h"
#include "game_root.h"

extern GameRoot* g_game; // data_4df904

char BorderManager::queue_frontend_widget_flag_after_delay(
    FrontendWidget* widget, int queued_flags)
{
    char result = delayed_widget_active;
    if (result == 0) {
        if ((widget->widget_flags & FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION) != 0)
            result = g_game->fade.begin_frontend_fade_out(0);
        delayed_widget = widget;
        delayed_widget_active = 1;
        delayed_widget_progress = 0.0f;
        delayed_widget_progress_step = 0.0833333358f;
        delayed_widget_flags = queued_flags;
    }
    return result;
}
