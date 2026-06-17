// request_object_vertex_colours @ 0x42f850 (fastcall, ret)

#include "object_render_types.h"
#include "sprite.h"

void* allocate_tracked_memory(int size, char* name);

void __fastcall request_object_vertex_colours(Object* mesh)
{
    mesh->vertex_colours =
        (Color4f*)allocate_tracked_memory(mesh->vertex_count << 4, "Object Vertex Colours List");
    int i = 0;
    int colour_index = 0;
    while (i < mesh->vertex_count) {
        ++i;
        mesh->vertex_colours[colour_index].r = 1.0f;
        mesh->vertex_colours[colour_index].g = 1.0f;
        mesh->vertex_colours[colour_index++].b = 1.0f;
    }
}
