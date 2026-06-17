// initialize_frontend_overlay_color_lerp @ 0x40ab00 (thiscall, ret 0x4)

#include "frontend_overlay_color_lerp.h"

int FrontendOverlayColorLerp::initialize_frontend_overlay_color_lerp(int state_)
{
    state = state_;
    current.store_color4f(0x3f800000, 0x3f800000, 0x3f800000, 0);
    return target.store_color4f(0x3f800000, 0x3f800000, 0x3f800000, 0);
}
