// initialize_salt_hazard_pool @ 0x441540 (thiscall, ret)

#include "salt_hazard_types.h"

void SaltManager::initialize_salt_hazard_pool()
{
    SaltState* state = &slots[0].state;
    int count = sizeof(slots) / sizeof(slots[0]);
    do {
        *state = SALT_STATE_INACTIVE;
        state += sizeof(Salt) / sizeof(SaltState);
        --count;
    } while (count);
}
