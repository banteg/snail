// Shared path-attachment sample layout.
#ifndef ATTACHMENT_SAMPLE_H
#define ATTACHMENT_SAMPLE_H

#include "transform_matrix.h"
#include "vector3.h"

struct AttachmentSample {            // stride 0xa8
    TransformMatrix transform;        // +0x00
    float inverse_matrix[16];         // +0x40, full local-frame transform
    Vector3 delta_dir_to_next;        // +0x80
    float delta_length;               // +0x8c, segment length (the swept-entry
                                      // "depth limit" gate is z < this)
    float center_x;                   // +0x90
    float rotation_scalar_94;         // +0x94
    float rotation_scalar_98;         // +0x98
    float lateral_scale;              // +0x9c
    float special_scalar;             // +0xa0, kind-42 scale/radius source
    float lateral_source;             // +0xa4
};

typedef char AttachmentSample_must_be_0xa8[
    (sizeof(AttachmentSample) == 0xa8) ? 1 : -1];

#endif
