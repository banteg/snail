// bind_subgame_owner @ 0x433fc0 (thiscall, ret)

#include "game_root.h"
#include "thanks_screen.h"


SubgameRuntime* SubgameOwnerLink::bind_subgame_owner()
{
    SubgameRuntime* result = &g_game->subgame;
    game = result;
    return result;
}
