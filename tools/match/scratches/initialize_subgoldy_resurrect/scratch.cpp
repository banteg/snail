// initialize_subgoldy_resurrect @ 0x441fa0 (thiscall, ret 0x4)

#include "player.h"

int Player::initialize_subgoldy_resurrect(int final_loss)
{
    resurrect_active = 1;
    resurrect_final_loss = final_loss;
    resurrect_progress = 0.0f;
    resurrect_progress_step = 0.00833333377f;
    return final_loss;
}
