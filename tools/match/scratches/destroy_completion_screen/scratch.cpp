// destroy_completion_screen @ 0x406060 (thiscall, ret)

#include "exit.h"
#include "game_root.h"


void cRExit::UnInit()
{
    g_game->border_manager.kill_border(prompt_title);
    g_game->border_manager.kill_border(yes_button);
    g_game->border_manager.kill_border(no_button);
    g_game->border_manager.unhide_all_borders();
    g_game->players[0].frontend_state = previous_frontend_state;
}
