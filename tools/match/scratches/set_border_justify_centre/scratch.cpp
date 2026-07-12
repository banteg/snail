// set_border_justify_centre @ 0x404730 (thiscall, ret 0x4)

#include "border_manager.h"

int BorderManager::set_border_justify_centre(int justify_centre_bits_)
{
    justify_centre_bits = justify_centre_bits_;
    return justify_centre_bits_;
}
