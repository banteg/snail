// unhide_all_borders @ 0x403400 (thiscall, ret)

#include "border_manager.h"

void BorderManager::unhide_all_borders()
{
    border_stack.apply_all_border_visibility_mode(1);
}
