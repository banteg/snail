// D3DX math entry points the recovered renderer calls that have no recovered
// body. D3DX 8 dispatched its math through per-CPU function tables, so the
// game calls D3DXMatrixTranslation through a jump to whichever variant the
// table chose; every variant computes the same matrix.

#include <math.h>

#include "transform_matrix.h"

TransformMatrix* __stdcall initialize_translation_matrix(TransformMatrix* matrix, float x, float y, float z);  // @ 0x44fd90

extern "C" TransformMatrix* __stdcall D3DXMatrixTranslation(TransformMatrix* matrix, float x, float y, float z)
{
    return initialize_translation_matrix(matrix, x, y, z);
}

extern "C" Vector3* __stdcall D3DXVec3Normalize(Vector3* out, const Vector3* in)
{
    float length = sqrtf(in->x * in->x + in->y * in->y + in->z * in->z);
    float scale = length > 0 ? 1.0f / length : 0.0f;
    out->x = in->x * scale;
    out->y = in->y * scale;
    out->z = in->z * scale;
    return out;
}

// D3DXMatrixOrthoLH (@ 0x4503a8): a left-handed orthographic projection.
TransformMatrix* __stdcall build_orthographic_projection_matrix(
    TransformMatrix* matrix, float width, float height, float near_z, float far_z)
{
    float* m = (float*)matrix;
    for (int i = 0; i < 16; ++i)
        m[i] = 0;
    m[0] = 2.0f / width;
    m[5] = 2.0f / height;
    m[10] = 1.0f / (far_z - near_z);
    m[14] = near_z / (near_z - far_z);
    m[15] = 1.0f;
    return matrix;
}
