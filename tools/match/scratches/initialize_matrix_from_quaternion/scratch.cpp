// initialize_matrix_from_quaternion @ 0x44d820 (thiscall)

#include "quaternion.h"
#include "transform_matrix.h"

TransformMatrix::TransformMatrix(const Quaternion& quaternion)
{
    float xx = quaternion.x * quaternion.x;
    float xy = quaternion.y * quaternion.x;
    float xz = quaternion.z * quaternion.x;
    float xw = quaternion.w * quaternion.x;
    float yy = quaternion.y * quaternion.y;
    float yz = quaternion.z * quaternion.y;
    float yw = quaternion.w * quaternion.y;
    float zz = quaternion.z * quaternion.z;
    float zw = quaternion.w * quaternion.z;

    basis_right.x = 1.0f - 2.0f * (zz + yy);
    basis_up.x = 2.0f * (xy - zw);
    basis_forward.x = 2.0f * (yw + xz);
    basis_right.y = 2.0f * (zw + xy);
    basis_up.y = 1.0f - 2.0f * (zz + xx);
    basis_forward.y = 2.0f * (yz - xw);
    basis_right.z = 2.0f * (xz - yw);
    basis_up.z = 2.0f * (yz + xw);
    basis_forward.z = 1.0f - 2.0f * (yy + xx);
    basis_forward_w = 0.0f;
    basis_up_w = 0.0f;
    basis_right_w = 0.0f;
    position.z = 0.0f;
    position.y = 0.0f;
    position.x = 0.0f;
    position_w = 1.0f;
}
