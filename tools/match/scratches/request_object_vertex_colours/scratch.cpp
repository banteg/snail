// cRObject::RequestColours() / request_object_vertex_colours @ 0x42f850

#include "object_render_types.h"
#include "sprite.h"

void* allocate_tracked_memory(int size, char* name);

void Object::request_object_vertex_colours()
{
    vertex_colours =
        (tColour*)allocate_tracked_memory(
            vertex_count * sizeof(tColour), "Object Vertex Colours List");
    int i = 0;
    int colour_index = 0;
    while (i < vertex_count) {
        ++i;
        vertex_colours[colour_index].r = 1.0f;
        vertex_colours[colour_index].g = 1.0f;
        vertex_colours[colour_index++].b = 1.0f;
    }
}
