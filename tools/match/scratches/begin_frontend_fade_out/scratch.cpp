// begin_frontend_fade_out @ 0x40abc0 (thiscall, ret 0x4)

#include "border_delay_lane.h"

int FrontendFade::begin_frontend_fade_out(int hold_state_)
{
    state = 2;
    alpha_bits = 0;
    hold_state = hold_state_;
    return hold_state_;
}
