// Shared overlay transform state, used by the initializer and per-frame update.
#ifndef OVERLAY_H
#define OVERLAY_H

#include "render_camera_slot.h"

class Overlay : public RenderableBod {
public:
    void initialize_overlay(); // @ 0x40a240
    void update_overlay(); // @ 0x40a1b0

    char unknown_078[0x80 - 0x78];
    // Viewport slots 0, 2, and 3 borrow the camera subobjects from the three
    // root-owned Overlay instances. The parent transform drives its camera.
    RenderCamera camera; // +0x80, ends at +0x148
    float rotation_step; // +0x148
};

typedef char Overlay_must_be_0x14c[(sizeof(Overlay) == 0x14c) ? 1 : -1];

#endif
