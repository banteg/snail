// initialize_backdrop_corner_quad @ 0x41a290 (cdecl)

#include "object_render_types.h"

extern int g_backdrop_corner_vertex_indices[4]; // 0x4a3ce0

void initialize_backdrop_slice_quad(Object* object, char* texture_path, float x_offset);

void initialize_backdrop_corner_quad(int selector, Object* object, char* texture_path)
{
    initialize_backdrop_slice_quad(object, texture_path, 0.0f);

    Vector3* vertices = object->vertices;
    Vector3* vertex = &vertices[g_backdrop_corner_vertex_indices[selector]];
    float component_value = vertex->x;
    float* component = &vertex->x;

    int sign;
    if (component_value < 0.0f) {
        sign = -1;
    } else {
        sign = 0;
        if (*component != 0.0f) {
            sign = 1;
        }
    }
    *component = (float)sign * 0.30000001f;

    int vertex_index = g_backdrop_corner_vertex_indices[selector];
    component_value = vertices[vertex_index].z;
    component = &vertices[vertex_index].z;
    if (component_value < 0.0f) {
        sign = -1;
    } else {
        sign = 0;
        if (*component != 0.0f) {
            sign = 1;
        }
    }
    *component = (float)sign * 0.30000001f;
}
