#ifndef VAPOUR_TRAIL_TYPES_H
#define VAPOUR_TRAIL_TYPES_H

typedef unsigned char uint8_t;
typedef int int32_t;

typedef struct Object Object;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct TransformMatrix {
    Vec3 basis_right;
    float basis_right_w;
    Vec3 basis_up;
    float basis_up_w;
    Vec3 basis_forward;
    float basis_forward_w;
    Vec3 position;
    float position_w;
} TransformMatrix;

typedef struct VapourQuadVertices {
    Vec3 corner_a;
    Vec3 corner_b;
    Vec3 corner_c;
    Vec3 corner_d;
} VapourQuadVertices;

/* Exact 0x94-byte Windows cRVapour owner. */
typedef struct Vapour {
    void* vtable;
    int32_t flags;
    uint8_t _pad_08[0x1c];
    Object* owner;
    uint8_t _pad_28[0x58];
    int32_t point_count;
    int32_t capacity;
    union {
        int32_t half_width_bits;
        float half_width;
    };
    float* z_floor;
    TransformMatrix* points;
} Vapour;

#endif
