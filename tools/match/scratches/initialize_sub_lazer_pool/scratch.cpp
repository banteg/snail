// initialize_sub_lazer_pool @ 0x441650 (thiscall, ret)
// Authored owner: cRSubLazerManager::Init().

#include "sub_lazer_types.h"

void cRSubLazerManager::Init()
{
    SubLazerState* state = &slots[0].state;
    int count = sizeof(slots) / sizeof(slots[0]);
    do {
        *state = SUB_LAZER_STATE_INACTIVE;
        state += sizeof(cRSubLazer) / sizeof(SubLazerState);
        --count;
    } while (count);
}
