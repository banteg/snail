// kill_all_borders @ 0x4033c0 (thiscall)

#include "border_manager.h"

void BorderManager::kill_all_borders()
{
    int result = 0;
    for (int i = 0; i < BORDER_RECORD_COUNT; ++i) {
        result = borders[i].flags;
        if (result != 0 && (result & 0x10000400) == 0) {
            result = (result & 0xffffff01) | 0x200;
            borders[i].flags = result;
        }
    }
}
