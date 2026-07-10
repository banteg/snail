// Vapour trail runtime view, partial.
#ifndef VAPOUR_TRAIL_H
#define VAPOUR_TRAIL_H

#include "transform_matrix.h"

struct VapourQuadVertices {
    Vector3 corner_a; // +0x00
    Vector3 corner_b; // +0x0c
    Vector3 corner_c; // +0x18
    Vector3 corner_d; // +0x24
};

class VapourTrailOwner {
public:
    char unknown_00[0x2c];
    int vertex_count; // +0x2c, point_count * 4 - 4
    char unknown_30[0x38 - 0x30];
    VapourQuadVertices* vertices; // +0x38
    char unknown_3c[0x54 - 0x3c];
    int max_points; // +0x54
    char unknown_58[0x5c - 0x58];
    int* vertex_attributes; // +0x5c, 0x30-byte stride
    char unknown_60[0xd4 - 0x60];
    int* index_count_out; // +0xd4
};

class VapourTrail {
public:
    virtual int update_vapour();
    int initialize_vapour(int unused, int half_width_bits); // @ 0x442500
    int reset_vapour(float* z_floor);                    // @ 0x442540
    void add_vapour_point(const TransformMatrix* point);  // @ 0x442560

    int flags; // +0x04
    char unknown_08[0x24 - 0x08];
    VapourTrailOwner* owner; // +0x24
    char unknown_28[0x80 - 0x28];
    int point_count;  // +0x80
    int capacity;     // +0x84
    union {
        int half_width_bits; // +0x88, initializer/raw callsite view
        float half_width;    // +0x88, update_vapour render width
    };
    float* z_floor; // +0x8c, optional position-z clamp source
    TransformMatrix* points; // +0x90
};

#endif
