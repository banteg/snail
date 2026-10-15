// Windows projection of the authored cRFlash full-screen color interpolator.
#ifndef FRONTEND_OVERLAY_COLOR_LERP_H
#define FRONTEND_OVERLAY_COLOR_LERP_H

#include "sprite.h"

class cRFlash {
public:
    void Init(int state); // @ 0x40ab00
    void AI(); // @ 0x40ab40

    int state; // +0x00
    tColour target; // +0x04
    tColour current; // +0x14
};

// Compatibility vocabulary retained for existing Windows-analysis callers.
typedef cRFlash FrontendOverlayColorLerp;

typedef char cRFlash_must_be_0x24[(sizeof(cRFlash) == 0x24) ? 1 : -1];
typedef char FrontendOverlayColorLerp_must_be_0x24[
    (sizeof(FrontendOverlayColorLerp) == 0x24) ? 1 : -1];

#endif
