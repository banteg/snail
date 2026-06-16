// initialize_jetpack_gauge @ 0x43a930 (thiscall, returns 0)

#include "jetpack_gauge.h"

extern char* g_game_base; // data_4df904

int JetpackGaugeController::initialize_jetpack_gauge(int player_slot)
{
    progress = 0.0f;
    char* game_ptr = g_game_base + 0x74618;
    progress_step = 0.00166666671f;
    game = game_ptr;
    char* player_ptr = g_game_base + 0x42fd7c;
    state = 0;
    player = player_ptr;
    wobble_alpha = 0.0f;
    wobble_y = 0.0f;
    wobble_x = 0.0f;
    warning_intensity_latch = 0.0f;
    return 0;
}
