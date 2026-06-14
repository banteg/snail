// initialize_matrix_from_quaternion @ 0x44d820 (thiscall)

#include "vector_types.h"

struct Quaternion {
    float x;
    float y;
    float z;
    float w;
};

struct TransformMatrix {
    Vec4 basis_right;
    Vec4 basis_up;
    Vec4 basis_forward;
    Vec4 position;

    TransformMatrix* initialize_matrix_from_quaternion(const Quaternion* quaternion);
};

TransformMatrix* TransformMatrix::initialize_matrix_from_quaternion(const Quaternion* quaternion)
{
    float xx = quaternion->x * quaternion->x;
    float xy = quaternion->y * quaternion->x;
    float xz = quaternion->z * quaternion->x;
    float xw = quaternion->w * quaternion->x;
    float yy = quaternion->y * quaternion->y;
    float yz = quaternion->z * quaternion->y;
    float yw = quaternion->w * quaternion->y;
    float zz = quaternion->z * quaternion->z;
    float zw = quaternion->w * quaternion->z;

    basis_right.x = 1.0f - (zz + yy + zz + yy);
    basis_up.x = xy - zw + xy - zw;
    basis_forward.x = yw + xz + yw + xz;
    basis_right.y = zw + xy + zw + xy;
    basis_up.y = 1.0f - (zz + xx + zz + xx);
    basis_forward.y = yz - xw + yz - xw;
    basis_right.z = xz - yw + xz - yw;
    basis_up.z = yz + xw + yz + xw;
    basis_forward.z = 1.0f - (yy + xx + yy + xx);
    basis_forward.w = 0.0f;
    basis_up.w = 0.0f;
    basis_right.w = 0.0f;
    position.z = 0.0f;
    position.y = 0.0f;
    position.x = 0.0f;
    position.w = 1.0f;
    return this;
}
