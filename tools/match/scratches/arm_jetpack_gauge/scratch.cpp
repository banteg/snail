// arm_jetpack_gauge / cRSubHover::On @ 0x43a980 (thiscall, ret)

#include "game_root.h"
#include "sub_hover.h"


void cRSubHover::On()
{
    if (state == SUB_HOVER_STATE_INACTIVE) {
        state = SUB_HOVER_STATE_ACTIVE;
        progress = 0.0f;
        wobble_alpha = 0.0f;
        wobble_y = 0.0f;
        wobble_x = 0.0f;

        g_game->subgame.embedded_player()->presentation.set_snail_jetpack(1);
        JetInit();
    }
}
