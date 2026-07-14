// initialize_invincible_shell @ 0x444ac0 (thiscall, ret)
#include "game_root.h"
#include "invincible.h"
#include "snail_skin.h"

extern GameRoot* g_game; // data_4df904

void Invincible::initialize_invincible_shell()
{
    state = 0;
    g_game->subgame.embedded_player()->presentation.snail_skin
        .change_snail_skin(0, 0.0f);
}
