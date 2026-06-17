// uninit_times_up @ 0x445e70 (thiscall, ret)

#include "border_manager.h"
#include "times_up_controller.h"

extern char* g_game_base; // data_4df904

void TimesUpController::uninit_times_up()
{
    if (state != 0) {
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(border);
    }
}
