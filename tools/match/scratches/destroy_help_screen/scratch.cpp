// destroy_help_screen @ 0x4168c0 (thiscall)

#include "game_root.h"
#include "help.h"


void Help::destroy_help_screen()
{
    g_game->border_manager.kill_all_borders();
}
