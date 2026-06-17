#ifndef VAPOUR_TRAIL_TYPES_H
#define VAPOUR_TRAIL_TYPES_H

typedef unsigned char uint8_t;
typedef int int32_t;

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

typedef struct VapourTrailOwner {
    uint8_t _pad_00[0x2c];
    int32_t vertex_count;
    uint8_t _pad_30[0x8];
    VapourQuadVertices* vertices;
    uint8_t _pad_3c[0x18];
    int32_t max_points;
    uint8_t _pad_58[0x4];
    int32_t* vertex_attributes;
    uint8_t _pad_60[0x74];
    int32_t* index_count_out;
} VapourTrailOwner;

typedef struct VapourTrail {
    void* vtable;
    int32_t flags;
    uint8_t _pad_08[0x1c];
    VapourTrailOwner* owner;
    uint8_t _pad_28[0x58];
    int32_t point_count;
    int32_t capacity;
    float half_width;
    int32_t z_floor;
    TransformMatrix* points;
} VapourTrail;

#endif
