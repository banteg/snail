// destroy_completion_screen @ 0x406060 (thiscall, ret)

#include "exit.h"
#include "game_root.h"

extern GameRoot* g_game; // data_4df904

void Exit::destroy_completion_screen()
{
    g_game->border_manager.kill_border(prompt_title);
    g_game->border_manager.kill_border(yes_button);
    g_game->border_manager.kill_border(no_button);
    g_game->border_manager.unhide_all_borders();
    g_game->players[0].frontend_state = previous_frontend_state;
}
