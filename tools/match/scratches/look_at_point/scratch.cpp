// look_at_point @ 0x44d4e0 (thiscall, ret 0x4)
//
// The native stack frame holds two Vector3 objects: the inlined `operator-`
// result temp at [esp..0x8] and the address-taken `delta` local at
// [esp+0xc..0x14], copied from the temp. That two-object layout is the
// signature of `Vector3 delta = *target - position;` with a by-value
// `operator-`, so the operator is recovered here rather than faked.

#include "transform_matrix.h"

void TransformMatrix::look_at_point(const Vector3& target)
{
    Vector3 delta = target - position;
    set_matrix_z_direction(delta);
}
