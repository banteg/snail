// uninit_pause_menu @ 0x440600 (thiscall, ret)

#include "game_root.h"
#include "pause_menu.h"

extern GameRoot* g_game; // data_4df904

void SubPause::uninit_pause_menu()
{
    g_game->border_manager.kill_border(options_widget);
    g_game->border_manager.kill_border(end_game_widget);
    g_game->border_manager.kill_border(resume_widget);
    g_game->players[0].mouse_cursor.release_mouse_cursor();
}
