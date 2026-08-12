// ObjectProcTileFastRamp @ 0x41a170 (cdecl)

#include "object_render_types.h"

extern int g_backdrop_raise_first_vertex_index; // 0x4a3c40
extern int g_backdrop_raise_second_vertex_index; // 0x4a3c44

void ObjectProcTileFastRamp(int selector, Object* object)
{
    Vector3* vertices = object->vertices;

    if (selector <= 0) {
        vertices[g_backdrop_raise_first_vertex_index].y += 0.5f;
        if (selector < 0) {
            return;
        }
    }

    vertices[g_backdrop_raise_second_vertex_index].y += 0.5f;
}
