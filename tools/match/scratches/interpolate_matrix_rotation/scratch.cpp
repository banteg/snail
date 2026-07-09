// interpolate_matrix_rotation @ 0x44d920 (thiscall, ret 0x4)
// Quaternion-based rotation interpolation: extract quat from the matrix,
// snap near-zero imaginary lanes, convert to axis-angle, scale the angle
// by alpha, recompose. When the axis collapses, rebuild from the snapped
// quaternion directly; when the angle is exactly zero, leave the matrix.
#include "quaternion.h"
#include "axis.h"
#include "transform_matrix.h"

struct AxisAngle {
    AxisAngle(); // out-of-line default ctor in the image

    float x;
    float y;
    float z;
    float angle;
};

void TransformMatrix::interpolate_matrix_rotation(float alpha)
{
    Quaternion working;
    AxisAngle axis;
    Quaternion extracted(&basis_right.x);
    working.x = extracted.x;
    working.y = extracted.y;
    working.z = extracted.z;
    working.w = extracted.w;
    if (working.x > -0.001f && working.x < 0.001f)
        working.x = 0.0f;
    if (*(volatile float*)&working.y > -0.001f && *(volatile float*)&working.y < 0.001f)
        working.y = 0.0f;
    if (*(volatile float*)&working.z > -0.001f && *(volatile float*)&working.z < 0.001f)
        working.z = 0.0f;
    if (working.x == 0.0f && working.y == 0.0f && working.z == 0.0f) {
        TransformMatrix rebuilt;
        rebuilt.initialize_matrix_from_quaternion(&working);
        *this = rebuilt;
    } else {
        ((Axis*)&axis)->initialize_axis_from_quaternion(&working);
        if (axis.angle != 0.0f) {
            axis.angle = axis.angle * alpha;
            working.initialize_quaternion_from_axis((Axis*)&axis);
            TransformMatrix rebuilt;
            rebuilt.initialize_matrix_from_quaternion(&working);
            *this = rebuilt;
        }
    }
}
