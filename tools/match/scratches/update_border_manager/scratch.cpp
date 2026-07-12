// update_border_manager @ 0x403fc0 (thiscall)

#include "border_manager.h"
#include "frontend_fade.h"

extern char* g_game_base; // data_4df904

void BorderManager::update_border_manager()
{
    if (delayed_widget_active != 0) {
        float progress = delayed_widget_progress_step + delayed_widget_progress;
        delayed_widget_progress = progress;
        if (progress > 1.0f) {
            FrontendWidget* widget = delayed_widget;
            delayed_widget_progress = 1.0f;
            unsigned int widget_flags = widget->widget_flags;
            if ((widget_flags & 0x40000000) == 0 ||
                ((FrontendFade*)(g_game_base + 0x24))->state == 4) {
                widget->widget_flags = widget_flags | delayed_widget_flags;
                delayed_widget_active = 0;
            }
        }
    }
}
