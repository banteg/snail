// uninit_thanks_screen @ 0x4340c0 (thiscall, ret)

#include "game_root.h"
#include "thanks_screen.h"


void ThanksScreen::uninit_thanks_screen()
{
    g_game->border_manager.kill_border(message_widget);
    g_game->players[0].frontend_state = 14;
}
