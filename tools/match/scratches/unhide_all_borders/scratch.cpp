// unhide_all_borders @ 0x403400 (thiscall, ret)

#include "border_manager.h"

int BorderManager::unhide_all_borders()
{
    return border_stack.apply_all_border_visibility_mode(1);
}
