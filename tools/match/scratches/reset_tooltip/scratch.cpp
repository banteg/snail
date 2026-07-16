// reset_tooltip @ 0x403be0 (thiscall, ret)

#include "frontend_widget.h"
#include "game_root.h"


void FrontendWidgetTooltip::reset_tooltip()
{
    switch (state) {
    case 3:
        g_game->border_manager.kill_border(tooltip_widget);
        tooltip_widget = 0;
        // Fall through to the shared idle-state reset.
    case 2:
        state = 1;
        return;
    default:
        return;
    }
}
