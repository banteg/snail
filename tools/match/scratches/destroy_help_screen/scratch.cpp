// destroy_help_screen @ 0x4168c0 (thiscall)

#include "border_manager.h"
#include "help.h"

extern char* g_game_base; // data_4df904

int Help::destroy_help_screen()
{
    return ((BorderManager*)(g_game_base + 0xb4c))->kill_all_borders();
}
