#ifndef OBJECT_ANIMATION_TYPES_H
#define OBJECT_ANIMATION_TYPES_H

#include "bod_types.h"
#include "vector3.h"

struct Object;

enum {
    OBJECT_ANIMATION_MODE_LOOP = 1,
    OBJECT_ANIMATION_MODE_PING_PONG = 2,
    OBJECT_ANIMATION_MODE_ONCE = 4,
    OBJECT_ANIMATION_MODE_ONCE_REVERSE = 8,
    OBJECT_ANIMATION_MODE_UNCHANGED = -1,
};

struct XAnimationKeyframe : public BodBase {
    char unknown_38[0x7c - 0x38];
    int frame_number; // +0x7c
};

typedef char XAnimationKeyframe_must_be_0x80[
    (sizeof(XAnimationKeyframe) == 0x80) ? 1 : -1];

struct ObjectAnimationFrame {
    Vector3* vertices; // +0x00
    Vector3* facequad_normals; // +0x04, two normals / 0x18 bytes per facequad
};

typedef char ObjectAnimationFrame_must_be_0x08[
    (sizeof(ObjectAnimationFrame) == 0x08) ? 1 : -1];

struct ObjectAnimation {
    unsigned short flags; // +0x00
    char unknown_02[0x04 - 0x02];
    int generated_frame_count; // +0x04
    ObjectAnimationFrame** frames; // +0x08
    float progress; // +0x0c
    float progress_step; // +0x10
};

typedef char ObjectAnimation_must_be_0x14[
    (sizeof(ObjectAnimation) == 0x14) ? 1 : -1];

#endif
