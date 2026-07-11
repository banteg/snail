// initialize_snail_skin @ 0x445f60 (thiscall, ret)
#include "player.h"

extern char* g_game_base; // data_4df904

void SnailSkin::initialize_snail_skin()
{
    Snail* owner = (Snail*)(g_game_base + 0x432700);
    selected_slot = 0;
    active = 0;
    owner_snail = owner;
}
