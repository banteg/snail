// initialize_frontend_overlay_color_lerp @ 0x40ab00 (thiscall, ret 0x4)

#include "frontend_overlay_color_lerp.h"

void FrontendOverlayColorLerp::initialize_frontend_overlay_color_lerp(int state_)
{
    state = state_;
    target.store_color4f(1.0f, 1.0f, 1.0f, 0.0f);
    current.store_color4f(1.0f, 1.0f, 1.0f, 0.0f);
}
