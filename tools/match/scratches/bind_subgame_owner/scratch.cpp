// bind_subgame_owner @ 0x433fc0 (thiscall, ret)

#include "thanks_screen.h"

extern char* g_game_base; // data_4df904

SubgameRuntime* SubgameOwnerLink::bind_subgame_owner()
{
    SubgameRuntime* result = (SubgameRuntime*)(g_game_base + 0x74618);
    game = result;
    return result;
}
