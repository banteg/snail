// kill_tip_widgets @ 0x4489e0 (thiscall, ret)

#include "tip_manager.h"

extern char* g_game_base; // data_4df904

struct BorderManager {
    void kill_border(FrontendWidget* border);
};

void TipSlot::kill_tip_widgets()
{
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(widget_main);
    if (widget_ok != 0) {
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(widget_ok);
    }
    if (widget_disable != 0) {
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(widget_disable);
    }
    active = 0;
}
