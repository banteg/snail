// request_object_vertices @ 0x42f710 (thiscall, ret 0x4)

#include "object_render_types.h"

void* allocate_tracked_memory(int size, char* name);
void free_tracked_memory(void* ptr);
int report_errorf(char* format, ...);

void __fastcall request_object_vertex_colours(Object* mesh);

void Object::request_object_vertices(int requested_count)
{
    if (requested_count > 0x10000)
        report_errorf("Too many Vertices");

    int current_count = vertex_count;
    if (current_count > 0 && current_count < requested_count) {
        report_errorf("Reallocation of Vertices impending\n");
        free_tracked_memory(vertices);
        vertex_count = 0;
    }

    if (vertex_count == 0) {
        vertex_count = requested_count;
        vertices = (Vector3*)allocate_tracked_memory(requested_count * 0xc, "Object Vertex List");
        request_object_vertex_colours(this);
    }
}
