// update_vapour @ 0x4425f0 (thiscall, ret)

#include "object_render_types.h"
#include "vapour.h"

inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 result;
    result.x = lhs.x + rhs.x;
    result.y = lhs.y + rhs.y;
    result.z = lhs.z + rhs.z;
    return result;
}

void Vapour::update_vapour()
{
    int count = point_count;
    if (count < 2) {
        int result = flags;
        result &= ~0x20;
        flags = result;
        return;
    }

    flags |= 0x20;
    owner->vertex_count = (count << 2) - 4;

    if (z_floor != 0) {
        for (int clamp_index = 0; clamp_index < point_count; ++clamp_index) {
            float* p_z = &points[clamp_index].position.z;
            if (*p_z < *z_floor)
                *p_z = *z_floor;
        }
    }

    float uv_mid = 0.5f;
    for (int segment = 0; segment < point_count - 1; ++segment) {
        owner->vertices[segment * 4] =
            points[segment].basis_right * half_width + points[segment].position;
        owner->vertices[segment * 4 + 1] =
            points[segment].basis_right * -half_width + points[segment].position;
        owner->vertices[segment * 4 + 2] =
            points[segment].basis_right * -half_width + points[segment + 1].position;
        owner->vertices[segment * 4 + 3] =
            points[segment].basis_right * half_width + points[segment + 1].position;

        int current_count = point_count;
        if (current_count == 2) {
            owner->facequads[segment].uv[0].v = 0.0f;
            owner->facequads[segment].uv[1].v = 0.0f;
            owner->facequads[segment].uv[2].v = 1.0f;
            owner->facequads[segment].uv[3].v = 1.0f;
        } else if (segment == 0) {
            owner->facequads[0].uv[0].v = 0.0f;
            owner->facequads[0].uv[1].v = 0.0f;
            owner->facequads[0].uv[2].v = uv_mid;
            owner->facequads[0].uv[3].v = uv_mid;
        } else if (segment == current_count - 2) {
            owner->facequads[segment].uv[0].v = uv_mid;
            owner->facequads[segment].uv[1].v = uv_mid;
            owner->facequads[segment].uv[2].v = 1.0f;
            owner->facequads[segment].uv[3].v = 1.0f;
        } else {
            owner->facequads[segment].uv[0].v = uv_mid;
            owner->facequads[segment].uv[1].v = uv_mid;
            owner->facequads[segment].uv[2].v = uv_mid;
            owner->facequads[segment].uv[3].v = uv_mid;
        }

    }

    int result = point_count * 2 - 2;
    *owner->group_primitive_counts = result;
}
