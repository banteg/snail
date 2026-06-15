// linear_interpolate_matrix @ 0x44da90 (thiscall, ret 0xc)
// tMatrix::LinearInterpolate per Android symbols: rotation interpolated in
// matrix space (invert/multiply/interpolate/premultiply/orthogonalize),
// translation blended linearly.
#include "transform_matrix.h"

void TransformMatrix::linear_interpolate_matrix(
    const TransformMatrix* from, const TransformMatrix* to, float alpha)
{
    invert_matrix_from_source(from);
    multiply_matrix_in_place(to);
    interpolate_matrix_rotation(alpha);
    premultiply_matrix_in_place(from);
    orthogonalize_matrix();
    float ty = alpha * to->position.y;
    float tz = alpha * to->position.z;
    float inv = 1.0f - alpha;
    float fx = inv * from->position.x;
    float fy = inv * from->position.y;
    float fz = inv * from->position.z;
    float ox = fx + alpha * to->position.x;
    position.x = ox;
    float oy = fy + ty;
    position.y = oy;
    float oz = fz + tz;
    position.z = oz;
}
