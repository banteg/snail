// initialize_sub_lazer_pool @ 0x441650 (thiscall, ret)

#include "sub_lazer_types.h"

int* SubLazerPool::initialize_sub_lazer_pool()
{
    int* state = &slots[0].state;
    int count = 20;
    do {
        *state = 0;
        state += 44;
        --count;
    } while (count);
    return state;
}
