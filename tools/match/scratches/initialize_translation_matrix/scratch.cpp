// initialize_translation_matrix @ 0x44fd90 (stdcall, ret 0x10)

#include "transform_matrix.h"

TransformMatrix* __stdcall initialize_translation_matrix(
    TransformMatrix* matrix,
    float x,
    float y,
    float z)
{
    float* slots = (float*)matrix;

    slots[11] = 0.0f;
    slots[12] = x;
    slots[9] = 0.0f;
    slots[13] = y;
    slots[8] = 0.0f;
    slots[14] = z;
    slots[7] = 0.0f;
    slots[6] = 0.0f;
    slots[4] = 0.0f;
    slots[3] = 0.0f;
    slots[2] = 0.0f;
    slots[1] = 0.0f;
    slots[15] = 1.0f;
    slots[10] = 1.0f;
    slots[5] = 1.0f;
    slots[0] = 1.0f;
    return matrix;
}
