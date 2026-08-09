// end_jetpack_hover / cRSubHover::End @ 0x43a370 (thiscall, ret)

#include "sub_hover.h"

void cRSubHover::End()
{
    if (state == SUB_HOVER_STATE_ACTIVE && progress < 0.94f) {
        progress = 0.94f;
    }
}
