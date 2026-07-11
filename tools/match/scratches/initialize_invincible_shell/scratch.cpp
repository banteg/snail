// initialize_invincible_shell @ 0x444ac0 (thiscall, ret)
#include "invincible.h"
#include "snail_skin.h"

extern char* g_game_base; // data_4df904

void Invincible::initialize_invincible_shell()
{
    state = 0;
    ((SnailSkinTransition*)(g_game_base + 0x434038))->change_snail_skin(0, 0.0f);
}
