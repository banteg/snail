// reset_tooltip @ 0x403be0 (thiscall, ret)

#include "frontend_widget.h"
#include "game_root.h"

extern GameRoot* g_game; // data_4df904

int FrontendWidgetTooltip::reset_tooltip()
{
    int result = state;
    result -= 2;
    if (result != 0) {
        --result;
        if (result != 0)
            return result;

        result = g_game->border_manager.kill_border(tooltip_widget);
        tooltip_widget = 0;
    }

    state = 1;
    return result;
}
