// uninit_times_up @ 0x445e70 (thiscall, ret)

#include "times_up_controller.h"

extern char* g_game_base; // data_4df904

struct BorderManager {
    void kill_border(FrontendWidget* border);
};

void TimesUpController::uninit_times_up()
{
    if (state != 0) {
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(border);
    }
}
