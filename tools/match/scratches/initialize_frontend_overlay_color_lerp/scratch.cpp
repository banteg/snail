// initialize_frontend_overlay_color_lerp @ 0x40ab00 (thiscall, ret 0x4)

#include "sprite.h"

class FrontendOverlayColorLerp {
public:
    int initialize_frontend_overlay_color_lerp(int state);

    int state;        // +0x00
    Color4f current;  // +0x04
    Color4f target;   // +0x14
};

int FrontendOverlayColorLerp::initialize_frontend_overlay_color_lerp(int state_)
{
    state = state_;
    current.store_color4f(0x3f800000, 0x3f800000, 0x3f800000, 0);
    return target.store_color4f(0x3f800000, 0x3f800000, 0x3f800000, 0);
}
