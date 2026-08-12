// Authored cROverlay transform state, used by Init and the per-frame AI.
#ifndef OVERLAY_H
#define OVERLAY_H

#include "viewport.h"

class cROverlay : public RenderableBod {
public:
    void Init(); // @ 0x40a240
    void AI(); // @ 0x40a1b0

    // Viewport slots 0, 2, and 3 borrow the camera subobjects from the three
    // root-owned cROverlay instances. The parent transform drives its camera.
    cRCamera camera; // +0x80, ends at +0x148
    float rotation_step; // +0x148
};

typedef cROverlay Overlay;

typedef char cROverlay_must_be_0x14c[
    (sizeof(cROverlay) == 0x14c) ? 1 : -1];
typedef char Overlay_must_be_0x14c[(sizeof(Overlay) == 0x14c) ? 1 : -1];

#endif
