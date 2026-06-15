// initialize_salt_hazard_pool @ 0x441540 (thiscall, ret)

#include "salt_hazard_types.h"

int* SaltHazardPool::initialize_salt_hazard_pool()
{
    int* state = &slots[0].state;
    int count = 40;
    do {
        *state = 0;
        state += 38;
        --count;
    } while (count);
    return state;
}
