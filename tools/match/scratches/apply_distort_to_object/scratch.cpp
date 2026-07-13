// apply_distort_to_object @ 0x41aa50 (thiscall)

#include "object_render_types.h"

float sine(float angle); // @ 0x44c9d0

#define ABS_FLOAT(value) ((value) < 0.0f ? -(value) : (value))
#define MAX_FLOAT(lhs, rhs) ((lhs) < (rhs) ? (rhs) : (lhs))

void ObjectDistort::apply_distort_to_object(Object* object)
{
    bool distorted = false;
    Vector3* source = object->vertices;

    if (z_wave != 0.0f) {
        float z_range = MAX_FLOAT(
            ABS_FLOAT(object->bounds_min.z),
            ABS_FLOAT(object->bounds_max.z));

        int index = 0;
        if (object->vertex_count > 0) {
            do {
                object->copied_vertices[index].x = source[index].x;

                float z = ABS_FLOAT(object->vertices[index].z);

                object->copied_vertices[index].y =
                    (sine(z * 1.5707964f / z_range + 4.712389f) + 1.0f)
                    * z_wave + source[index].y;
                object->copied_vertices[index].z = source[index].z;
                ++index;
            } while (index < object->vertex_count);
        }

        source = object->copied_vertices;
        distorted = true;
    }

    if (y_squash != 0.0f) {
        float scale_x = sine(y_squash * 1.5707964f) + 1.0f;
        float squash_y = 1.0f - sine(y_squash * 1.5707964f);
        float base_y = object->bounds_min.y;

        int index = 0;
        if (object->vertex_count > 0) {
            do {
                object->copied_vertices[index].x = scale_x * source[index].x;
                object->copied_vertices[index].y =
                    (source[index].y - base_y) * squash_y + base_y;
                object->copied_vertices[index].z = source[index].z;
                ++index;
            } while (index < object->vertex_count);
        }

        source = object->copied_vertices;
        distorted = true;
    }

    if (xyz_scale != 0.0f) {
        float scale_xy = sine(xyz_scale * 1.5707964f) * 0.1f + 1.0f;
        float scale_z = 1.0f - sine(xyz_scale * 1.5707964f);

        int index = 0;
        if (object->vertex_count > 0) {
            do {
                object->copied_vertices[index].x = scale_xy * source[index].x;
                object->copied_vertices[index].y = scale_xy * source[index].y;
                object->copied_vertices[index].z = scale_z * source[index].z;
                ++index;
            } while (index < object->vertex_count);
        }
    } else if (!distorted) {
        return;
    }

    object->vertices = object->copied_vertices;
    object->calc_object_facequad_normals_simple();
}
