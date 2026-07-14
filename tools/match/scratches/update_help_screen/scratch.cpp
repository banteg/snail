// update_help_screen @ 0x4168d0 (thiscall)

#include "game_root.h"
#include "help.h"

extern GameRoot* g_game; // data_4df904

void Help::update_help_screen()
{
    FrontendWidget* button = back_button;
    unsigned int flags = button->widget_flags;
    if ((flags & 0x20) != 0) {
        button->widget_flags = flags & ~0x20u;
        destroy_help_screen();
        g_game->players[0].frontend_state = 2;
        g_game->players[0].redispatch_requested = 1;
    }
}
