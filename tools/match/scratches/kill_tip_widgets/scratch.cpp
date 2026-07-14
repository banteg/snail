// kill_tip_widgets @ 0x4489e0 (thiscall, ret)

#include "game_root.h"
#include "tip_manager.h"

extern GameRoot* g_game; // data_4df904

void Tip::kill_tip_widgets()
{
    g_game->border_manager.kill_border(widget_main);
    if (widget_ok != 0) {
        g_game->border_manager.kill_border(widget_ok);
    }
    if (widget_disable != 0) {
        g_game->border_manager.kill_border(widget_disable);
    }
    active = 0;
}
