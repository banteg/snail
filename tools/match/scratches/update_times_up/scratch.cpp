// update_times_up @ 0x445e20 (thiscall, ret)

#include "game_root.h"
#include "player.h"
#include "times_up.h"

extern GameRoot* g_game; // data_4df904

void TimesUp::update_times_up()
{
    switch (state) {
        case 0:
            return;
        case 1:
            progress = progress_step + progress;
            if (progress > 1.0f) {
                state = 2;
            }
            break;
        case 2:
            uninit_times_up();
            g_game->subgame.player.kill_subgoldy();
            state = 0;
            break;
    }
}
