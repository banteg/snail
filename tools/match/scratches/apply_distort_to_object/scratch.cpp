// apply_distort_to_object @ 0x41aa50 (thiscall)

#include "object_render_types.h"

float sine(float angle); // @ 0x44c9d0

void ObjectDistort::apply_distort_to_object(Object* object)
{
    bool distorted = false;
    Vector3* source = object->vertices;

    if (z_wave != 0.0f) {
        float min_z = object->bounds_min.z;
        if (min_z < 0.0f) {
            min_z = -min_z;
        }

        float max_z = object->bounds_max.z;
        if (max_z < 0.0f) {
            max_z = -max_z;
        }

        float z_range;
        if (min_z >= max_z) {
            z_range = object->bounds_min.z;
            if (z_range < 0.0f) {
                z_range = -z_range;
            }
        } else {
            z_range = object->bounds_max.z;
            if (z_range < 0.0f) {
                z_range = -z_range;
            }
        }

        int index = 0;
        if (object->vertex_count > 0) {
            do {
                Vector3* out = &object->copied_vertices[index];
                Vector3* in = &source[index];
                out->x = in->x;

                float z = in->z;
                if (z < 0.0f) {
                    z = -z;
                }

                out->y = (sine(z * 1.5707964f / z_range + 4.712389f) + 1.0f)
                    * z_wave + in->y;
                out->z = in->z;
                ++index;
            } while (index < object->vertex_count);
        }

        source = object->copied_vertices;
        distorted = true;
    }

    if (y_squash != 0.0f) {
        float phase = y_squash * 1.5707964f;
        float scale_x = sine(phase) + 1.0f;
        float squash_y = 1.0f - sine(y_squash * 1.5707964f);
        float base_y = object->bounds_min.y;

        int index = 0;
        if (object->vertex_count > 0) {
            do {
                Vector3* out = &object->copied_vertices[index];
                Vector3* in = &source[index];
                out->x = scale_x * in->x;
                out->y = (in->y - base_y) * squash_y + base_y;
                out->z = in->z;
                ++index;
            } while (index < object->vertex_count);
        }

        source = object->copied_vertices;
        distorted = true;
    }

    if (xyz_scale == 0.0f) {
        if (!distorted) {
            return;
        }
    } else {
        float phase = xyz_scale * 1.5707964f;
        float scale_xy = sine(phase) * 0.1f + 1.0f;
        float scale_z = 1.0f - sine(xyz_scale * 1.5707964f);

        int index = 0;
        if (object->vertex_count > 0) {
            do {
                Vector3* out = &object->copied_vertices[index];
                Vector3* in = &source[index];
                out->x = scale_xy * in->x;
                out->y = scale_xy * in->y;
                out->z = scale_z * in->z;
                ++index;
            } while (index < object->vertex_count);
        }
    }

    object->vertices = object->copied_vertices;
    object->calc_object_facequad_normals_simple();
}
