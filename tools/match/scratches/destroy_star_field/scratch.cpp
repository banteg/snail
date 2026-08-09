// cRStarManager::UnInit @ 0x434270 (thiscall)

#include "star_manager.h"

void cRStarManager::UnInit()
{
    int i = 0;
    int result = count;
    for (; i < result; ++i) {
        entries[i].active = 0;
        entries[i].sprite->Kill();
        result = count;
    }

    state = 0;
}
