// hide_all_borders / cRBorderManager::HideBorders @ 0x4033f0

#include "border_manager.h"

void cRBorderManager::HideBorders()
{
    border_stack.apply_all_border_visibility_mode(0);
}
