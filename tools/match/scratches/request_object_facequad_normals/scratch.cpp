// request_object_facequad_normals @ 0x42f800 (thiscall, ret)

void* allocate_tracked_memory(int size, char* name);

class Object {
public:
    void* request_object_facequad_normals();

    char unknown_00[0x2c];
    int vertex_count; // +0x2c
    char unknown_30[0x44 - 0x30];
    void* vertex_normals; // +0x44
    char unknown_48[0x54 - 0x48];
    int facequad_count; // +0x54
    char unknown_58[0x60 - 0x58];
    void* facequad_normals; // +0x60
};

void* Object::request_object_facequad_normals()
{
    if (vertex_normals == 0)
        vertex_normals = allocate_tracked_memory(vertex_count * 0xc, "Object Vertex Normals List");

    void* result = facequad_normals;
    if (result == 0) {
        result = allocate_tracked_memory(facequad_count * 0x18, "Object FaceQuad Normals List");
        facequad_normals = result;
    }
    return result;
}
