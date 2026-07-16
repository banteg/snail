// update_help_screen @ 0x4168d0 (thiscall)

#include "game_root.h"
#include "help.h"


void Help::update_help_screen()
{
    FrontendWidget* button = back_button;
    unsigned int flags = button->widget_flags;
    if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
        button->widget_flags =
            flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
        destroy_help_screen();
        g_game->players[0].frontend_state = 2;
        g_game->players[0].redispatch_requested = 1;
    }
}
