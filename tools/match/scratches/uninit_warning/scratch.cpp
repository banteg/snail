// uninit_warning @ 0x446f10 (thiscall, tailcall)

#include "game_root.h"
#include "warning.h"


void Warning::uninit_warning()
{
    g_game->border_manager.kill_border(border);
}
