// get_or_append_object_texture_group_vertex @ 0x413bb0 (cdecl)

#include "sprite.h"
#include "object_render_types.h"
#include "vector3.h"

int report_errorf(char* format, ...);

int get_or_append_object_texture_group_vertex(
    Object* object, int vertex_index, float u, float v)
{
    if (vertex_index >= object->vertex_count) {
        report_errorf("VertexRef out of Range");
    }

    Vector3 position = object->vertices[vertex_index];

    int i = 0;
    for (; i < g_object_grouped_vertex_cursor; ++i) {
        if ((object->flags & OBJECT_FLAG_DYNAMIC_VERTICES) != 0) {
            if (g_object_grouped_vertex_scratch[i].source_vertex == vertex_index &&
                g_object_grouped_vertex_scratch[i].u == u &&
                g_object_grouped_vertex_scratch[i].v == 1.0f - v) {
                return i;
            }
        } else if (g_object_grouped_vertex_scratch[i].x == position.x &&
            g_object_grouped_vertex_scratch[i].y == position.y &&
            g_object_grouped_vertex_scratch[i].z == position.z &&
            g_object_grouped_vertex_scratch[i].u == u &&
            g_object_grouped_vertex_scratch[i].v == 1.0f - v) {
            return i;
        }
    }

    g_object_grouped_vertex_scratch[i].x = position.x;
    g_object_grouped_vertex_scratch[i].y = position.y;
    g_object_grouped_vertex_scratch[i].z = position.z;
    g_object_grouped_vertex_scratch[i].u = u;
    g_object_grouped_vertex_scratch[i].v = 1.0f - v;

    if ((object->flags & OBJECT_FLAG_USE_VERTEX_COLOURS) != 0) {
        ((tColourSmall*)&g_object_grouped_vertex_scratch[i].diffuse)->operator=(
            object->vertex_colours[vertex_index]);
    } else {
        g_object_grouped_vertex_scratch[i].diffuse = 0xffffffff;
    }

    g_object_grouped_vertex_scratch[i].source_vertex = vertex_index;

    ++g_object_grouped_vertex_cursor;
    return g_object_grouped_vertex_cursor - 1;
}
