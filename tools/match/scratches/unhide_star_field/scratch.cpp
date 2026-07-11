// unhide_star_field @ 0x4346b0 (thiscall, ret int)

#include "star_manager.h"

int StarManager::unhide_star_field()
{
    int result = state;
    if (result != 0) {
        result = count;
        for (int i = 0; i < result; ++i) {
            entries[i].sprite->flags |= 0x40;
            result = count;
        }
    }
    return result;
}
