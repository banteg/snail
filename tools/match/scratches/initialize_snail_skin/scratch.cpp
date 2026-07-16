// initialize_snail_skin @ 0x445f60 (thiscall, ret)
#include "game_root.h"
#include "player.h"


void SnailSkin::initialize_snail_skin()
{
    Snail* owner = &g_game->subgame.embedded_player()->presentation;
    selected_slot = SNAIL_SKIN_SLOT_DEFAULT;
    active = 0;
    owner_snail = owner;
}
