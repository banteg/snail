// end_jetpack_hover @ 0x43a370 (thiscall, ret)

#include "sub_hover.h"

void SubHover::end_jetpack_hover()
{
    if (state == SUB_HOVER_STATE_ACTIVE && progress < 0.94f) {
        progress = 0.94f;
    }
}
