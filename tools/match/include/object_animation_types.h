#ifndef OBJECT_ANIMATION_TYPES_H
#define OBJECT_ANIMATION_TYPES_H

#include "vector3.h"

struct ObjectAnimationFrame {
    Vector3* vertices; // +0x00
    void* facequad_normals; // +0x04, 0x18 bytes per facequad
};

struct ObjectAnimation {
    unsigned short flags; // +0x00
    char unknown_02[0x04 - 0x02];
    int generated_frame_count; // +0x04
    ObjectAnimationFrame** frames; // +0x08
    float progress; // +0x0c
    float progress_step; // +0x10
};

#endif
