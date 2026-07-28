// Shared 4x4 transform matrix view. This is the row layout used by the math
// routines and by renderable bodies at +0x38.
#ifndef TRANSFORM_MATRIX_H
#define TRANSFORM_MATRIX_H

#include "transform_matrix_fwd.h"
#include "quaternion_fwd.h"
#include "vector3.h"
#include "vector_types.h"

struct tMatrix {
    tMatrix() {}
    tMatrix(float scale); // @ 0x44cde0
    tMatrix(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33); // @ 0x44cfe0
    tMatrix(const tQuaternian& quaternion); // @ 0x44d820
    // ABI compatibility view for partial callers that copy from the
    // constructor's EAX result. The owned definition is the overload above.
    tMatrix* initialize_matrix_from_values(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33); // @ 0x44cfe0
    void operator*=(const tMatrix& rhs); // @ 0x44d1a0
    void Multiply(const tMatrix& rhs); // @ 0x44d1d0
    void PreMultiply(const tMatrix& lhs); // @ 0x44d1e0
    void Multiply(const tMatrix& lhs, const tMatrix& rhs); // @ 0x44d060
    void Invert(); // @ 0x44d280
    void Invert(const tMatrix& source); // @ 0x44d330
    void LinearInterpolate(
        const tMatrix& from,
        const tMatrix& to,
        float alpha); // @ 0x44da90
    void Interpolate(float alpha); // @ 0x44d920
    void Orthoganalize(); // @ 0x44d3d0, authored spelling
    void Identity(); // @ 0x44d210
    void RotIdentity(); // @ 0x44d250
    void RotLocalX(float angle); // @ 0x44ce30
    void RotLocalY(float angle); // @ 0x44cec0
    void RotLocalZ(float angle); // @ 0x44cf50
    void SetZDir(const tVector& direction); // @ 0x44d410
    void LookAt(const tVector& target); // @ 0x44d4e0

    tVector basis_right;   // +0x00
    float basis_right_w;   // +0x0c
    tVector basis_up;      // +0x10
    float basis_up_w;      // +0x1c
    tVector basis_forward; // +0x20
    float basis_forward_w; // +0x2c
    tVector position;      // +0x30
    float position_w;      // +0x3c
};

typedef char tMatrix_must_be_0x40[(sizeof(tMatrix) == 0x40) ? 1 : -1];

// Compatibility surface for partial scratches not yet converted to the
// authored member spelling. The ABI is identical: transform is passed in ECX.
void __fastcall set_matrix_identity(TransformMatrix* transform); // @ 0x44d210

#endif
