// advance_blink_random @ 0x4408a0 (thiscall, ret)

#include "subgame_runtime.h"

double SubgameRuntime::advance_blink_random()
{
    int next_index = (blink_random_index + 1) % 24;
    blink_random_index = next_index;
    return blink_random_samples[next_index];
}
