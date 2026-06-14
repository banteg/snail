// request_object_vertex_colours @ 0x42f850 (fastcall, ret)

void* allocate_tracked_memory(int size, char* name);

struct Color4f {
    float r;
    float g;
    float b;
    float a;
};

class Object {
public:
    char unknown_00[0x2c];
    int vertex_count; // +0x2c
    char unknown_30[0x48 - 0x30];
    Color4f* vertex_colours; // +0x48
};

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
