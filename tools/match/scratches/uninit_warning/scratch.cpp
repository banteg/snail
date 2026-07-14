// uninit_warning @ 0x446f10 (thiscall, tailcall)

#include "game_root.h"
#include "warning.h"

extern GameRoot* g_game; // data_4df904

void Warning::uninit_warning()
{
    g_game->border_manager.kill_border(border);
}
