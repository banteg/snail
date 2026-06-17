// destroy_help_screen @ 0x4168c0 (cdecl)

#include "border_manager.h"

extern char* g_game_base; // data_4df904

int destroy_help_screen()
{
    return ((BorderManager*)(g_game_base + 0xb4c))->kill_all_borders();
}
