// uninit_times_up @ 0x445e70 (thiscall, ret)

#include "game_root.h"
#include "times_up.h"

extern GameRoot* g_game; // data_4df904

void TimesUp::uninit_times_up()
{
    if (state != TIMES_UP_STATE_INACTIVE) {
        g_game->border_manager.kill_border(border);
    }
}
