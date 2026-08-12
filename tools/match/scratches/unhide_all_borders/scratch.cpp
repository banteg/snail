// unhide_all_borders / cRBorderManager::UnHideBorders @ 0x403400

#include "border_manager.h"

void cRBorderManager::UnHideBorders()
{
    border_stack.apply_all_border_visibility_mode(1);
}
