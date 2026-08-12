// update_help_screen @ 0x4168d0 (thiscall)

#include "game_root.h"
#include "help.h"


void cRHelp::AI()
{
    FrontendWidget* button = back_button;
    unsigned int flags = button->widget_flags;
    if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
        button->widget_flags =
            flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
        UnInit();
        g_game->players[0].frontend_state = 2;
        g_game->players[0].redispatch_requested = 1;
    }
}
