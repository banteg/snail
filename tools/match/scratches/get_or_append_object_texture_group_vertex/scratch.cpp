// get_or_append_object_texture_group_vertex @ 0x413bb0 (cdecl)

#include "sprite.h"
#include "vector3.h"

int report_errorf(char* format, ...);

struct ColorBGRA8 {
    ColorBGRA8* pack_color_rgba_u8(Color4f*); // @ 0x44dbf0

    unsigned char b;
    unsigned char g;
    unsigned char r;
    unsigned char a;
};

struct ObjectGroupedVertex {
    float x;              // +0x00
    float y;              // +0x04
    float z;              // +0x08
    unsigned int diffuse; // +0x0c
    float u;              // +0x10
    float v;              // +0x14, stored as 1.0 - source v
    int source_vertex;    // +0x18
};

struct ObjectTextureGroupVertexView {
    char unknown_00[0x10];
    unsigned int flags; // +0x10
    char unknown_14[0x2c - 0x14];
    int vertex_count; // +0x2c
    char unknown_30[0x38 - 0x30];
    Vector3* vertices; // +0x38
    char unknown_3c[0x48 - 0x3c];
    Color4f* vertex_colours; // +0x48
};

extern int g_object_grouped_vertex_cursor; // data_5031bc
extern ObjectGroupedVertex* g_object_grouped_vertex_scratch; // data_5031c4

int get_or_append_object_texture_group_vertex(
    ObjectTextureGroupVertexView* object, int vertex_index, float u, float v)
{
    if (vertex_index >= object->vertex_count) {
        report_errorf("VertexRef out of Range");
    }

    Vector3* source = &object->vertices[vertex_index];
    int position_bits[3];
    position_bits[0] = *(int*)&source->x;
    position_bits[1] = *(int*)&source->y;
    position_bits[2] = *(int*)&source->z;

    int i = 0;
    int count = g_object_grouped_vertex_cursor;
    if (count > 0) {
        ObjectGroupedVertex* cursor = g_object_grouped_vertex_scratch;
        if ((object->flags & 4) != 0) {
            do {
                if (cursor->source_vertex == vertex_index &&
                    cursor->u == u &&
                    cursor->v == 1.0f - v) {
                    return i;
                }
                ++i;
                ++cursor;
            } while (i < count);
        } else {
            do {
                if (cursor->x == *(float*)&position_bits[0] &&
                    cursor->y == *(float*)&position_bits[1] &&
                    cursor->z == *(float*)&position_bits[2] &&
                    cursor->u == u &&
                    cursor->v == 1.0f - v) {
                    return i;
                }
                ++i;
                ++cursor;
            } while (i < count);
        }
    }

    ObjectGroupedVertex* appended = &g_object_grouped_vertex_scratch[i];
    appended->x = *(float*)&position_bits[0];
    appended->y = *(float*)&position_bits[1];
    appended->z = *(float*)&position_bits[2];
    appended->u = u;
    appended->v = 1.0f - v;

    if ((object->flags & 0x10000) != 0) {
        ((ColorBGRA8*)&appended->diffuse)->pack_color_rgba_u8(
            &object->vertex_colours[vertex_index]);
    } else {
        g_object_grouped_vertex_scratch[i].diffuse = 0xffffffff;
    }

    g_object_grouped_vertex_scratch[i].source_vertex = vertex_index;

    int result = g_object_grouped_vertex_cursor;
    g_object_grouped_vertex_cursor = result + 1;
    return result;
}
