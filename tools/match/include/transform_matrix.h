// Shared 4x4 transform matrix view. This is the row layout used by the math
// routines and by renderable bodies at +0x38.
#ifndef TRANSFORM_MATRIX_H
#define TRANSFORM_MATRIX_H

#include "vector3.h"
#include "vector_types.h"

struct TransformMatrix {
    TransformMatrix* initialize_uniform_scale_matrix(float scale); // @ 0x44cde0
    TransformMatrix* initialize_matrix_from_values(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33); // @ 0x44cfe0
    TransformMatrix* multiply_matrix_in_place(TransformMatrix* rhs); // @ 0x44d1a0
    TransformMatrix* premultiply_matrix_in_place(TransformMatrix* rhs); // @ 0x44d1e0
    TransformMatrix* multiply_matrices(const TransformMatrix* lhs, const TransformMatrix* rhs);
    void set_matrix_rotation_identity();              // @ 0x44d250
    void rotate_matrix_world_x(float angle);          // @ 0x44ce30
    void rotate_matrix_world_y(float angle);          // @ 0x44cec0
    void rotate_matrix_world_z(float angle);          // @ 0x44cf50
    void set_matrix_z_direction(const Vector3* direction); // @ 0x44d410

    Vec4 basis_right;   // +0x00
    Vec4 basis_up;      // +0x10
    Vec4 basis_forward; // +0x20
    Vec4 position;      // +0x30
};

typedef char TransformMatrix_must_be_0x40[(sizeof(TransformMatrix) == 0x40) ? 1 : -1];

void __fastcall set_matrix_identity(TransformMatrix* transform); // @ 0x44d210

#endif
