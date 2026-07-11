// initialize_jetpack_gauge @ 0x43a930 (thiscall, ret 0x4)

#include "game_root.h"
#include "sub_hover.h"

extern GameRoot* g_game; // data_4df904

void SubHover::initialize_jetpack_gauge(int player_slot)
{
    progress = 0.0f;
    SubgameRuntime* game_ptr = &g_game->subgame;
    progress_step = 0.00166666671f;
    game = game_ptr;
    Player* player_ptr = g_game->subgame.embedded_player();
    state = 0;
    player = player_ptr;
    wobble_alpha = 0.0f;
    wobble_y = 0.0f;
    wobble_x = 0.0f;
    warning_intensity_latch = 0.0f;
}
