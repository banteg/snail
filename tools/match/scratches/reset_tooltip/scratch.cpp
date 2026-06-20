// reset_tooltip @ 0x403be0 (thiscall, ret)

#include "border_manager.h"
#include "frontend_widget.h"

extern char* g_game_base; // data_4df904

int TooltipState::reset_tooltip()
{
    int result = state;
    result -= 2;
    if (result != 0) {
        --result;
        if (result != 0)
            return result;

        result = ((BorderManager*)(g_game_base + 0xb4c))->kill_border(tooltip_widget);
        tooltip_widget = 0;
    }

    state = 1;
    return result;
}
