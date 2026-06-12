// request_object_vertices_copy @ 0x42f7d0 (thiscall, ret)

void* allocate_tracked_memory(int size, char* name);

class Object {
public:
    int request_object_vertices_copy();
    int copy_object_vertices();

    char unknown_00[0x2c];
    int vertex_count;
    char unknown_30[0x3c - 0x30];
    void* copied_vertices;
};

int Object::request_object_vertices_copy()
{
    copied_vertices = allocate_tracked_memory(vertex_count * 0xc, "Object Vertex List");
    return copy_object_vertices();
}
