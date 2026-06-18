// begin_frontend_fade_in @ 0x40abe0 (thiscall, ret)

#include "border_delay_lane.h"

void FrontendFade::begin_frontend_fade_in()
{
    state = 1;
    alpha_bits = 0x3f800000;
}
