// interpolate_matrix_rotation @ 0x44d920 (thiscall, ret 0x4)
// Quaternion-based rotation interpolation: extract quat from the matrix,
// snap near-zero imaginary lanes, convert to axis-angle, scale the angle
// by alpha, recompose. When the axis collapses, rebuild from the snapped
// quaternion directly; when the angle is exactly zero, leave the matrix.
#include "quaternion.h"
#include "axis.h"
#include "transform_matrix.h"

void TransformMatrix::interpolate_matrix_rotation(float alpha)
{
    Quaternion working;
    AxisAngle axis;
    Quaternion extracted(*this);
    working = extracted;
    if (working.x > -0.001f && working.x < 0.001f)
        working.x = 0.0f;
    if (working.y > -0.001f && working.y < 0.001f)
        working.y = 0.0f;
    if (working.z > -0.001f && working.z < 0.001f)
        working.z = 0.0f;
    if (working.x == 0.0f && working.y == 0.0f && working.z == 0.0f) {
        TransformMatrix rebuilt(working);
        *this = rebuilt;
    } else {
        axis = working;
        if (axis.angle != 0.0f) {
            axis.angle = axis.angle * alpha;
            working = axis;
            TransformMatrix rebuilt(working);
            *this = rebuilt;
        }
    }
}
