// cRBorderManager::HideBorders() / hide_all_borders @ 0x4033f0

#include "border_manager.h"

void cRBorderManager::hide_all_borders()
{
    border_stack.apply_all_border_visibility_mode(0);
}
