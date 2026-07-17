// update_vapour @ 0x4425f0 (thiscall, ret)

#include "object_render_types.h"
#include "vapour.h"

void Vapour::update_vapour()
{
    int count = point_count;
    if (count < 2) {
        int result = list_flags;
        result &= ~0x20;
        list_flags = result;
        return;
    }

    list_flags |= 0x20;
    object->vertex_count = (count << 2) - 4;

    if (z_floor != 0) {
        for (int clamp_index = 0; clamp_index < point_count; ++clamp_index) {
            float* p_z = &points[clamp_index].position.z;
            if (*p_z < *z_floor)
                *p_z = *z_floor;
        }
    }

    float uv_mid = 0.5f;
    for (int segment = 0; segment < point_count - 1; ++segment) {
        object->vertices[segment * 4] =
            points[segment].basis_right * half_width + points[segment].position;
        object->vertices[segment * 4 + 1] =
            points[segment].basis_right * -half_width + points[segment].position;
        object->vertices[segment * 4 + 2] =
            points[segment].basis_right * -half_width + points[segment + 1].position;
        object->vertices[segment * 4 + 3] =
            points[segment].basis_right * half_width + points[segment + 1].position;

        int current_count = point_count;
        if (current_count == 2) {
            object->facequads[segment].uv[0].v = 0.0f;
            object->facequads[segment].uv[1].v = 0.0f;
            object->facequads[segment].uv[2].v = 1.0f;
            object->facequads[segment].uv[3].v = 1.0f;
        } else if (segment == 0) {
            object->facequads[0].uv[0].v = 0.0f;
            object->facequads[0].uv[1].v = 0.0f;
            object->facequads[0].uv[2].v = uv_mid;
            object->facequads[0].uv[3].v = uv_mid;
        } else if (segment == current_count - 2) {
            object->facequads[segment].uv[0].v = uv_mid;
            object->facequads[segment].uv[1].v = uv_mid;
            object->facequads[segment].uv[2].v = 1.0f;
            object->facequads[segment].uv[3].v = 1.0f;
        } else {
            object->facequads[segment].uv[0].v = uv_mid;
            object->facequads[segment].uv[1].v = uv_mid;
            object->facequads[segment].uv[2].v = uv_mid;
            object->facequads[segment].uv[3].v = uv_mid;
        }

    }

    int result = point_count * 2 - 2;
    *object->group_primitive_counts = result;
}
