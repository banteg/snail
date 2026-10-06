// build_camera_view_matrix @ 0x451ad9 (stdcall, ret 0x10)

#include "transform_matrix.h"

extern "C" Vector3* __stdcall D3DXVec3Normalize(Vector3* out, const Vector3* in);

extern "C" TransformMatrix* __stdcall build_camera_view_matrix(
    TransformMatrix* matrix,
    const Vector3* eye,
    const Vector3* target,
    const Vector3* up)
{
    Vector3 forward;
    forward.x = eye->x - target->x;
    forward.y = eye->y - target->y;
    forward.z = eye->z - target->z;
    D3DXVec3Normalize(&forward, &forward);

    Vector3 right_source;
    right_source.x = forward.z * up->y - forward.y * up->z;
    right_source.y = forward.x * up->z - forward.z * up->x;
    right_source.z = forward.y * up->x - forward.x * up->y;

    Vector3 right = right_source;
    D3DXVec3Normalize(&right, &right);

    float up_x = forward.y * right.z - forward.z * right.y;
    float up_y = forward.z * right.x - forward.x * right.z;
    float up_z = forward.x * right.y - forward.y * right.x;

    float* out = (float*)matrix;
    out[0] = right.x;
    out[1] = up_x;
    out[2] = forward.x;
    out[3] = 0.0f;
    out[4] = right.y;
    out[5] = up_y;
    out[6] = forward.y;
    out[7] = 0.0f;
    out[8] = right.z;
    out[9] = up_z;
    out[10] = forward.z;
    out[11] = 0.0f;

    out[12] = -(right.x * eye->x + right.y * eye->y + right.z * eye->z);
    out[13] = -(up_x * eye->x + up_y * eye->y + up_z * eye->z);
    out[14] = -(forward.x * eye->x + forward.y * eye->y + forward.z * eye->z);
    out[15] = 1.0f;
    return matrix;
}
