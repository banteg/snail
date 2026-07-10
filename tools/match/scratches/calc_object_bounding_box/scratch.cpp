// calc_object_bounding_box @ 0x42fb10 (thiscall)

#include "object_render_types.h"
#include "vector3.h"

void Object::calc_object_bounding_box()
{
    Vector3* max = &bounds_max;
    *max = Vector3(-10000000000.0f, -10000000000.0f, -10000000000.0f);
    Vector3* min = &bounds_min;
    *min = Vector3(10000000000.0f, 10000000000.0f, 10000000000.0f);
    int offset = 0;
    bounding_radius = 0.0f;
    int result = 0;
    if (vertex_count > 0) {
        do {
            Vector3* vertex = (Vector3*)((char*)vertices + offset);

            float max_x;
            if (max->x <= vertex->x) {
                max_x = vertex->x;
            } else {
                max_x = bounds_max.x;
                max = &bounds_max;
            }
            max->x = max_x;

            float min_x;
            if (vertex->x <= min->x) {
                min_x = vertex->x;
            } else {
                min_x = bounds_min.x;
                min = &bounds_min;
            }
            min->x = min_x;

            float max_y;
            if (bounds_max.y <= vertex->y) {
                max_y = vertex->y;
            } else {
                max_y = bounds_max.y;
            }
            bounds_max.y = max_y;

            float min_y;
            if (vertex->y <= bounds_min.y) {
                min_y = vertex->y;
            } else {
                min_y = bounds_min.y;
            }
            bounds_min.y = min_y;

            float max_z;
            if (bounds_max.z <= vertex->z) {
                max_z = vertex->z;
            } else {
                max_z = bounds_max.z;
            }
            bounds_max.z = max_z;

            float min_z;
            if (vertex->z <= bounds_min.z) {
                min_z = vertex->z;
            } else {
                min_z = bounds_min.z;
            }
            bounds_min.z = min_z;

            float radius = vertex->vector_magnitude();
            if (radius > bounding_radius) {
                bounding_radius = radius;
            }

            ++result;
            offset += sizeof(Vector3);
        } while (result < vertex_count);
    }
}
