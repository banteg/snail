// update_vapour @ 0x4425f0 (thiscall, ret)

#include "vapour_trail.h"

int VapourTrail::update_vapour()
{
    int count = point_count;
    if (count < 2) {
        int result = flags;
        result &= ~0x20;
        flags = result;
        return result;
    }

    flags |= 0x20;
    owner->vertex_count = (count << 2) - 4;

    if (z_floor != 0) {
        int clamp_index = 0;
        if (point_count > 0) {
            int point_offset = 0;
            do {
                float* floor = z_floor;
                TransformMatrix* point =
                    (TransformMatrix*)((char*)points + point_offset);
                if (point->position.z < *floor)
                    point->position.z = *floor;
                ++clamp_index;
                point_offset += 0x40;
            } while (clamp_index < point_count);
        }
    }

    int segment = 0;
    if (point_count - 1 <= 0) {
        int result = point_count * 2 - 2;
        *owner->index_count_out = result;
        return result;
    }

    do {
        int point_offset = segment << 6;
        TransformMatrix* point = (TransformMatrix*)((char*)points + point_offset);
        int vertex_offset = segment * 0x30;
        VapourQuadVertices* vertices =
            (VapourQuadVertices*)((char*)owner->vertices + vertex_offset);

        float width = half_width;
        float corner_a_dx = width * point->basis_right.x;
        float corner_a_dy = width * point->basis_right.y;
        float corner_a_x = corner_a_dx + point->position.x;
        float corner_a_y = corner_a_dy + point->position.y;
        float corner_a_z = width * point->basis_right.z + point->position.z;
        vertices->corner_a.x = corner_a_x;
        vertices->corner_a.y = corner_a_y;
        vertices->corner_a.z = corner_a_z;

        float neg_width = -half_width;
        float corner_b_dx = neg_width * point->basis_right.x;
        float corner_b_dy = neg_width * point->basis_right.y;
        float corner_b_x = corner_b_dx + point->position.x;
        float corner_b_y = corner_b_dy + point->position.y;
        float corner_b_z = neg_width * point->basis_right.z + point->position.z;
        vertices->corner_b.x = corner_b_x;
        vertices->corner_b.y = corner_b_y;
        vertices->corner_b.z = corner_b_z;

        float neg_width_next = -half_width;
        float corner_c_dx = neg_width_next * point->basis_right.x;
        float corner_c_dy = neg_width_next * point->basis_right.y;
        float corner_c_x = corner_c_dx + point[1].position.x;
        float corner_c_y = corner_c_dy + point[1].position.y;
        float corner_c_z = neg_width_next * point->basis_right.z + point[1].position.z;
        vertices->corner_c.x = corner_c_x;
        vertices->corner_c.y = corner_c_y;
        vertices->corner_c.z = corner_c_z;

        float width_next = half_width;
        float corner_d_dx = width_next * point->basis_right.x;
        float corner_d_dy = width_next * point->basis_right.y;
        float corner_d_x = corner_d_dx + point[1].position.x;
        float corner_d_y = corner_d_dy + point[1].position.y;
        float corner_d_z = width_next * point->basis_right.z + point[1].position.z;
        vertices->corner_d.x = corner_d_x;
        vertices->corner_d.y = corner_d_y;
        vertices->corner_d.z = corner_d_z;

        int* attributes = (int*)((char*)owner->vertex_attributes + vertex_offset);
        int current_count = point_count;
        if (current_count == 2) {
            attributes[5] = 0;
            attributes[7] = 0;
            attributes[9] = 0x3f800000;
            attributes[11] = 0x3f800000;
        } else if (segment == 0) {
            owner->vertex_attributes[5] = 0;
            owner->vertex_attributes[7] = 0;
            owner->vertex_attributes[9] = 0x3f000000;
            owner->vertex_attributes[11] = 0x3f000000;
        } else {
            attributes[5] = 0x3f000000;
            attributes[7] = 0x3f000000;
            if (segment == current_count - 2) {
                attributes[9] = 0x3f000000;
                attributes[11] = 0x3f000000;
            } else {
                attributes[9] = 0x3f800000;
                attributes[11] = 0x3f800000;
            }
        }

        ++segment;
    } while (segment < point_count - 1);

    int result = point_count * 2 - 2;
    *owner->index_count_out = result;
    return result;
}
