// begin_frontend_fade_out @ 0x40abc0 (thiscall, ret 0x4)

#include "frontend_fade.h"

void cRFade::Start(FrontendFadeCallback completion_callback_)
{
    state = 2;
    alpha_bits = 0;
    completion_callback = completion_callback_;
}
