// initialize_invincible_shell @ 0x444ac0 (thiscall, ret)
#include "game_root.h"
#include "invincible.h"
#include "snail_skin.h"


void Invincible::initialize_invincible_shell()
{
    state = INVINCIBLE_STATE_INACTIVE;
    g_game->subgame.embedded_player()->presentation.snail_skin
        .change_snail_skin(SNAIL_SKIN_SLOT_DEFAULT, 0.0f);
}
