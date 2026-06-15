// initialize_matrix_from_values @ 0x44cfe0 (thiscall)

#include "transform_matrix.h"

TransformMatrix* TransformMatrix::initialize_matrix_from_values(
    float m00,
    float m01,
    float m02,
    float m03,
    float m10,
    float m11,
    float m12,
    float m13,
    float m20,
    float m21,
    float m22,
    float m23,
    float m30,
    float m31,
    float m32,
    float m33)
{
    basis_right.x = m00;
    basis_right.y = m01;
    basis_right.z = m02;
    basis_right_w = m03;
    basis_up.x = m10;
    basis_up.y = m11;
    basis_up.z = m12;
    basis_up_w = m13;
    basis_forward.x = m20;
    basis_forward.y = m21;
    basis_forward.z = m22;
    basis_forward_w = m23;
    position.x = m30;
    position.y = m31;
    position.z = m32;
    position_w = m33;
    return this;
}
