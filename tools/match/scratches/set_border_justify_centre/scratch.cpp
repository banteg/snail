// set_border_justify_centre @ 0x404730 (thiscall, ret 0x4)

#include "border_runtime.h"

int BorderRuntime::set_border_justify_centre(int justify_centre_)
{
    justify_centre = justify_centre_;
    return justify_centre_;
}
