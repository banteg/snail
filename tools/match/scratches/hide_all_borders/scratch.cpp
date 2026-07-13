// hide_all_borders @ 0x4033f0 (thiscall, ret)

#include "border_manager.h"

int BorderManager::hide_all_borders()
{
    return border_stack.apply_all_border_visibility_mode(0);
}
