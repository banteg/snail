// initialize_snail_skin @ 0x445f60 (thiscall, ret)
#include "game_root.h"
#include "player.h"

extern GameRoot* g_game; // data_4df904

void SnailSkin::initialize_snail_skin()
{
    Snail* owner = &g_game->subgame.embedded_player()->presentation;
    selected_slot = 0;
    active = 0;
    owner_snail = owner;
}
