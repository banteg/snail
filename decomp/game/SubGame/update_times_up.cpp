// update_times_up @ 0x445e20 (thiscall, ret)

#include "game_root.h"
#include "player.h"
#include "times_up.h"


void cRTimesUp::AI()
{
    switch (state) {
        case TIMES_UP_STATE_INACTIVE:
            return;
        case TIMES_UP_STATE_DISPLAYING:
            progress = progress_step + progress;
            if (progress > 1.0f) {
                state = TIMES_UP_STATE_EXPIRED;
            }
            break;
        case TIMES_UP_STATE_EXPIRED:
            UnInit();
            g_game->subgame.player.Kill();
            state = TIMES_UP_STATE_INACTIVE;
            break;
    }
}
