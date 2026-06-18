// Front-end full-screen overlay color lerp, shared by initialization and the
// per-frame draw/update root.
#ifndef FRONTEND_OVERLAY_COLOR_LERP_H
#define FRONTEND_OVERLAY_COLOR_LERP_H

#include "sprite.h"

class FrontendOverlayColorLerp {
public:
    int initialize_frontend_overlay_color_lerp(int state); // @ 0x40ab00
    void draw_frontend_overlay_color_lerp();

    int state; // +0x00
    Color4f target; // +0x04
    Color4f current; // +0x14
};

#endif
