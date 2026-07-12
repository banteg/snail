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
            if ((double)vertex->x < (double)max->x) {
                max_x = bounds_max.x;
                max = &bounds_max;
            } else {
                max_x = vertex->x;
            }
            max->x = max_x;

            float min_x;
            if ((double)min->x < (double)vertex->x) {
                min_x = bounds_min.x;
                min = &bounds_min;
            } else {
                min_x = vertex->x;
            }
            min->x = min_x;

            float max_y;
            if ((double)vertex->y < (double)bounds_max.y) {
                max_y = bounds_max.y;
            } else {
                max_y = vertex->y;
            }
            bounds_max.y = max_y;

            float min_y;
            if ((double)bounds_min.y < (double)vertex->y) {
                min_y = bounds_min.y;
            } else {
                min_y = vertex->y;
            }
            bounds_min.y = min_y;

            float max_z;
            if ((double)vertex->z < (double)bounds_max.z) {
                max_z = bounds_max.z;
            } else {
                max_z = vertex->z;
            }
            bounds_max.z = max_z;

            float min_z;
            if ((double)bounds_min.z < (double)vertex->z) {
                min_z = bounds_min.z;
            } else {
                min_z = vertex->z;
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
