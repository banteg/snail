// initialize_snail_skin @ 0x445f60 (thiscall, ret)
#include "snail_skin.h"

extern char* g_game_base; // data_4df904

void SnailSkinTransition::initialize_snail_skin()
{
    PlayerRenderOwner* owner = (PlayerRenderOwner*)(g_game_base + 0x432700);
    selected_slot = 0;
    active = 0;
    owner_render_state = owner;
}
