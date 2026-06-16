// update_times_up @ 0x445e20 (thiscall, ret)

#include "player.h"
#include "times_up_controller.h"

extern char* g_game_base; // data_4df904

void TimesUpController::update_times_up()
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
            ((Player*)(g_game_base + 0x42fd7c))->kill_subgoldy();
            state = 0;
            break;
    }
}
