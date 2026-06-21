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

    Vector3 to_weighted;
    to_weighted.x = alpha * to->position.x;
    to_weighted.y = alpha * to->position.y;
    to_weighted.z = alpha * to->position.z;

    float inv = 1.0f - alpha;

    Vector3 from_weighted;
    from_weighted.x = inv * from->position.x;
    from_weighted.y = inv * from->position.y;
    from_weighted.z = inv * from->position.z;

    Vector3 blended;
    blended.x = from_weighted.x + to_weighted.x;
    blended.y = from_weighted.y + to_weighted.y;
    blended.z = from_weighted.z + to_weighted.z;
    position = blended;
}
