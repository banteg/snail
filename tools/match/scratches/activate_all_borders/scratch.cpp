// activate_all_borders @ 0x403300 (thiscall, ret)

#include "border_manager.h"

void BorderManager::activate_all_borders()
{
    for (int i = 0; i < 150; ++i) {
        int flags = borders[i].flags;
        if ((flags & 0x80000000) == 0) {
            flags &= 0xffff7fff;
            borders[i].flags = flags;
        }
        borders[i].flags &= 0x7fffffff;
        borders[i].target_padding = borders[i].idle_padding;
        borders[i].active_padding = borders[i].idle_padding;
        borders[i].hover_blend_target = 0.0f;
    }
}
