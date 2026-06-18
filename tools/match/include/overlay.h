// Shared overlay transform state, used by the initializer and per-frame update.
#ifndef OVERLAY_H
#define OVERLAY_H

#include "transform_matrix.h"

class Overlay {
public:
    void initialize_overlay(); // @ 0x40a240
    void update_overlay(); // @ 0x40a1b0

    char unknown_000[0x38];
    TransformMatrix screen_matrix; // +0x38
    char unknown_078[0xb8 - 0x078];
    TransformMatrix world_matrix; // +0xb8
    char unknown_0f8[0x100 - 0x0f8];
    TransformMatrix inverse_screen_matrix; // +0x100
    float field_140; // +0x140
    float rotation_angle; // +0x144
    float rotation_step; // +0x148
};

typedef char Overlay_must_be_0x14c[(sizeof(Overlay) == 0x14c) ? 1 : -1];

#endif
