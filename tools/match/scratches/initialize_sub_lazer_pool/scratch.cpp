// initialize_sub_lazer_pool @ 0x441650 (thiscall, ret)

#include "sub_lazer_types.h"

void SubLazerManager::initialize_sub_lazer_pool()
{
    int* state = &slots[0].state;
    int count = sizeof(slots) / sizeof(slots[0]);
    do {
        *state = SUB_LAZER_STATE_INACTIVE;
        state += sizeof(SubLazer) / sizeof(int);
        --count;
    } while (count);
}
