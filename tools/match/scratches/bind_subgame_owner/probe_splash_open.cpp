// Independent control for the cRSplash::Open body folded at 0x433fc0.
// Build as a temporary scratch with SYMBOL=?Open@cRSplash@@QAEXXZ.
#include "game_root.h"
#include "thanks_screen.h"

void cRSplash::Open()
{
    game = &g_game->subgame;
}
