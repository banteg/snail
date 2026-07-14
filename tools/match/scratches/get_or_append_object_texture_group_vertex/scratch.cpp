// get_or_append_object_texture_group_vertex @ 0x413bb0 (cdecl)

#include "sprite.h"
#include "object_render_types.h"
#include "vector3.h"

int report_errorf(char* format, ...);

extern int g_object_grouped_vertex_cursor; // data_5031bc
extern ObjectGroupedVertex* g_object_grouped_vertex_scratch; // data_5031c4

int get_or_append_object_texture_group_vertex(
    Object* object, int vertex_index, float u, float v)
{
    if (vertex_index >= object->vertex_count) {
        report_errorf("VertexRef out of Range");
    }

    Vector3 position = object->vertices[vertex_index];

    int i = 0;
    int count = g_object_grouped_vertex_cursor;
    if (count > 0) {
        char* cursor = (char*)&g_object_grouped_vertex_scratch[0].y;
        int source_vertex_only = object->flags & 4;
        do {
            if (source_vertex_only != 0) {
                if (*(int*)(cursor + 0x14) == vertex_index &&
                    *(float*)(cursor + 0x0c) == u &&
                    *(float*)(cursor + 0x10) == 1.0f - v) {
                    return i;
                }
            } else if (*(float*)(cursor - 0x04) == position.x &&
                *(float*)cursor == position.y &&
                *(float*)(cursor + 0x04) == position.z &&
                *(float*)(cursor + 0x0c) == u &&
                *(float*)(cursor + 0x10) == 1.0f - v) {
                return i;
            }
            ++i;
            cursor += sizeof(ObjectGroupedVertex);
        } while (i < count);
    }

    g_object_grouped_vertex_scratch[i].x = position.x;
    g_object_grouped_vertex_scratch[i].y = position.y;
    g_object_grouped_vertex_scratch[i].z = position.z;
    g_object_grouped_vertex_scratch[i].u = u;
    g_object_grouped_vertex_scratch[i].v = 1.0f - v;

    if ((object->flags & 0x10000) != 0) {
        ((tColourSmall*)&g_object_grouped_vertex_scratch[i].diffuse)->pack_color_rgba_u8(
            &object->vertex_colours[vertex_index]);
    } else {
        g_object_grouped_vertex_scratch[i].diffuse = 0xffffffff;
    }

    g_object_grouped_vertex_scratch[i].source_vertex = vertex_index;

    ++g_object_grouped_vertex_cursor;
    return g_object_grouped_vertex_cursor - 1;
}
