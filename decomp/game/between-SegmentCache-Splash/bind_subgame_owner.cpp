// bind_subgame_owner @ 0x433fc0: folded cRGUI::Open / cRSplash::Open

#include "game_root.h"
#include "gui.h"

void cRGUI::Open()
{
    game = &g_game->subgame;
}
